/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2004-2007 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2022 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2008 High Performance Computing Center Stuttgart,
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2007      Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2012-2013 Los Alamos National Security, LLC.  All rights
 *                         reserved.
 * Copyright (c) 2014-2019 Research Organization for Information Science
 *                         and Technology (RIST).  All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#include "ompi_config.h"
#include <stdio.h>

#include "ompi/mpi/c/bindings.h"
#include "ompi/runtime/params.h"
#include "ompi/communicator/communicator.h"
#include "ompi/errhandler/errhandler.h"
#include "ompi/datatype/ompi_datatype.h"
#include "ompi/mca/coll/base/coll_base_util.h"
#include "ompi/memchecker.h"
#include "ompi/runtime/ompi_spc.h"

#if OMPI_BUILD_MPI_PROFILING
#if OPAL_HAVE_WEAK_SYMBOLS
#pragma weak MPI_Alltoallw_init = PMPI_Alltoallw_init
#endif
#define MPI_Alltoallw_init PMPI_Alltoallw_init
#endif

static const char FUNC_NAME[] = "MPI_Alltoallw_init";


int MPI_Alltoallw_init(const void *sendbuf, const int sendcounts[], const int sdispls[],
                       const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[],
                       const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm,
                       MPI_Info info, MPI_Request *request)
{
    int i, size, err;

    SPC_RECORD(OMPI_SPC_ALLTOALLW_INIT, 1);

    MEMCHECKER(
        ptrdiff_t recv_ext;
        ptrdiff_t send_ext;


        memchecker_comm(comm);

        size = OMPI_COMM_IS_INTER(comm)?ompi_comm_remote_size(comm):ompi_comm_size(comm);
        for ( i = 0; i < size; i++ ) {
            if (MPI_IN_PLACE != sendbuf) {
                memchecker_datatype(sendtypes[i]);
                ompi_datatype_type_extent(sendtypes[i], &send_ext);
                memchecker_call(&opal_memchecker_base_isdefined,
                                (char *)(sendbuf)+sdispls[i]*send_ext,
                                sendcounts[i], sendtypes[i]);
            }

            memchecker_datatype(recvtypes[i]);
            ompi_datatype_type_extent(recvtypes[i], &recv_ext);
            memchecker_call(&opal_memchecker_base_isaddressable,
                            (char *)(recvbuf)+rdispls[i]*recv_ext,
                            recvcounts[i], recvtypes[i]);
        }
    );

    if (MPI_PARAM_CHECK) {

        /* Unrooted operation -- same checks for all ranks */

        err = MPI_SUCCESS;
        OMPI_ERR_INIT_FINALIZE(FUNC_NAME);
        if (ompi_comm_invalid(comm)) {
            return OMPI_ERRHANDLER_NOHANDLE_INVOKE(MPI_ERR_COMM,
                                          FUNC_NAME);
        }

        if (MPI_IN_PLACE == sendbuf) {
            sendcounts = recvcounts;
            sdispls    = rdispls;
            sendtypes  = recvtypes;
        }

        if ((NULL == sendcounts) || (NULL == sdispls) || (NULL == sendtypes) ||
            (NULL == recvcounts) || (NULL == rdispls) || (NULL == recvtypes) ||
            (MPI_IN_PLACE == sendbuf && OMPI_COMM_IS_INTER(comm)) ||
            MPI_IN_PLACE == recvbuf) {
            return OMPI_ERRHANDLER_INVOKE(comm, MPI_ERR_ARG, FUNC_NAME);
        }

        size = OMPI_COMM_IS_INTER(comm)?ompi_comm_remote_size(comm):ompi_comm_size(comm);
        for (i = 0; i < size; ++i) {
            OMPI_CHECK_DATATYPE_FOR_SEND(err, sendtypes[i], sendcounts[i]);
            OMPI_ERRHANDLER_CHECK(err, comm, err, FUNC_NAME);
            OMPI_CHECK_DATATYPE_FOR_RECV(err, recvtypes[i], recvcounts[i]);
            OMPI_ERRHANDLER_CHECK(err, comm, err, FUNC_NAME);
        }

        if (MPI_IN_PLACE != sendbuf && !OMPI_COMM_IS_INTER(comm)) {
            int me = ompi_comm_rank(comm);
            size_t sendtype_size, recvtype_size;
            ompi_datatype_type_size(sendtypes[me], &sendtype_size);
            ompi_datatype_type_size(recvtypes[me], &recvtype_size);
            if ((sendtype_size*sendcounts[me]) != (recvtype_size*recvcounts[me])) {
                return OMPI_ERRHANDLER_INVOKE(comm, MPI_ERR_TRUNCATE, FUNC_NAME);
            }
        }
    }

    /* Invoke the coll component to perform the back-end operation */
    err = comm->c_coll->coll_alltoallw_init(sendbuf, sendcounts, sdispls,
                                            sendtypes, recvbuf, recvcounts,
                                            rdispls, recvtypes, comm, info, request,
                                            comm->c_coll->coll_alltoallw_init_module);
    if (OPAL_LIKELY(OMPI_SUCCESS == err)) {
        ompi_coll_base_retain_datatypes_w(*request, (MPI_IN_PLACE==sendbuf)?NULL:sendtypes, recvtypes, false);
    }
    OMPI_ERRHANDLER_RETURN(err, comm, err, FUNC_NAME);
}


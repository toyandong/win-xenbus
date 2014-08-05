/* Copyright (c) Citrix Systems Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, 
 * with or without modification, are permitted provided 
 * that the following conditions are met:
 * 
 * *   Redistributions of source code must retain the above 
 *     copyright notice, this list of conditions and the 
 *     following disclaimer.
 * *   Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the 
 *     following disclaimer in the documentation and/or other 
 *     materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE.
 */

#ifndef _XEN_H
#define _XEN_H

#include <ntddk.h>

#include <xen-version.h>
#include <xen-types.h>
#include <xen-warnings.h>
#include <xen-errno.h>
#include <xen/memory.h>
#include <xen/event_channel.h>
#include <xen/grant_table.h>
#include <xen/sched.h>
#include <xen/hvm/params.h>
#include <xen/io/xs_wire.h>

#ifndef XEN_API
#define XEN_API __declspec(dllimport)
#endif  // XEN_API

// Dummy function to cause XEN.SYS to be loaded and initialized
XEN_API
VOID
XenTouch(
    VOID
    );

// HVM

__checkReturn
XEN_API
NTSTATUS
HvmSetParam(
    IN  ULONG       Parameter,
    IN  ULONG_PTR   Value
    );

__checkReturn
XEN_API
NTSTATUS
HvmGetParam(
    IN  ULONG       Parameter,
    OUT PULONG_PTR  Value
    );

__checkReturn
XEN_API
NTSTATUS
HvmGetTime(
    OUT PLARGE_INTEGER  Now
    );

__checkReturn
XEN_API
NTSTATUS
HvmPagetableDying(
    IN  PHYSICAL_ADDRESS    Address
    );

// MEMORY

__checkReturn
XEN_API
NTSTATUS
MemoryAddToPhysmap(
    IN  PFN_NUMBER  Pfn,
    IN  ULONG       Space,
    IN  ULONG_PTR   Offset
    );

__checkReturn
XEN_API
ULONG
MemoryDecreaseReservation(
    IN  ULONG       Count,
    IN  PPFN_NUMBER PfnArray
    );

__checkReturn
XEN_API
ULONG
MemoryPopulatePhysmap(
    IN  ULONG       Count,
    IN  PPFN_NUMBER PfnArray
    );

// EVENT CHANNEL

__checkReturn
XEN_API
NTSTATUS
EventChannelSend(
    IN  evtchn_port_t   Port
    );

__checkReturn
XEN_API
NTSTATUS
EventChannelAllocateUnbound(
    IN  domid_t         Domain,
    OUT evtchn_port_t   *Port
    );

__checkReturn
XEN_API
NTSTATUS
EventChannelBindInterDomain(
    IN  domid_t                     RemoteDomain,
    IN  evtchn_port_t               RemotePort,
    OUT evtchn_port_t               *LocalPort
    );

__checkReturn
XEN_API
NTSTATUS
EventChannelBindVirq(
    IN  uint32_t            Virq,
    OUT evtchn_port_t       *LocalPort
    );

__checkReturn
XEN_API
NTSTATUS
EventChannelClose(
    IN  evtchn_port_t   LocalPort
    );

// GRANT TABLE

__checkReturn
XEN_API
NTSTATUS
GrantTableSetVersion(
    IN  uint32_t    Version
    );

__checkReturn
XEN_API
NTSTATUS
GrantTableGetVersion(
    OUT uint32_t    *Version
    );

__checkReturn
XEN_API
NTSTATUS
GrantTableCopy(
    IN  struct gnttab_copy  op[],
    IN  ULONG               Count
    );

// SCHED

__checkReturn
XEN_API
NTSTATUS
SchedShutdownCode(
    ULONG   Reason
    );

__checkReturn
XEN_API
NTSTATUS
SchedShutdown(
    ULONG   Reason
    );

XEN_API
VOID
SchedYield(
    VOID
    );

// MODULE

XEN_API
VOID
ModuleLookup(
    IN  ULONG_PTR   Address,
    OUT PCHAR       *Name,
    OUT PULONG_PTR  Offset
    );

// LOG

typedef enum _LOG_LEVEL {
    LOG_LEVEL_INVALID = 0,
    LOG_LEVEL_TRACE = 1 << DPFLTR_TRACE_LEVEL,
    LOG_LEVEL_INFO = 1 << DPFLTR_INFO_LEVEL,
    LOG_LEVEL_WARNING = 1 << DPFLTR_WARNING_LEVEL,
    LOG_LEVEL_ERROR = 1 << DPFLTR_ERROR_LEVEL,
    LOG_LEVEL_CRITICAL = 0x80000000
} LOG_LEVEL, *PLOG_LEVEL;

XEN_API
VOID
LogCchVPrintf(
    IN  LOG_LEVEL   Level,
    IN  ULONG       Count,
    IN  const CHAR  *Format,
    IN  va_list     Arguments
    );

XEN_API
VOID
LogVPrintf(
    IN  LOG_LEVEL   Level,
    IN  const CHAR  *Format,
    IN  va_list     Arguments
    );

XEN_API
VOID
LogCchPrintf(
    IN  LOG_LEVEL   Level,
    IN  ULONG       Count,
    IN  const CHAR  *Format,
    ...
    );

XEN_API
VOID
LogPrintf(
    IN  LOG_LEVEL   Level,
    IN  const CHAR  *Format,
    ...
    );

#endif  // _XEN_H

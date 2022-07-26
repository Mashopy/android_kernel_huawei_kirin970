/*
* Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
* foss@huawei.com
*
* If distributed as part of the Linux kernel, the following license terms
* apply:
*
* * This program is free software; you can redistribute it and/or modify
* * it under the terms of the GNU General Public License version 2 and
* * only version 2 as published by the Free Software Foundation.
* *
* * This program is distributed in the hope that it will be useful,
* * but WITHOUT ANY WARRANTY; without even the implied warranty of
* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* * GNU General Public License for more details.
* *
* * You should have received a copy of the GNU General Public License
* * along with this program; if not, write to the Free Software
* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*
* Otherwise, the following license terms apply:
*
* * Redistribution and use in source and binary forms, with or without
* * modification, are permitted provided that the following conditions
* * are met:
* * 1) Redistributions of source code must retain the above copyright
* *    notice, this list of conditions and the following disclaimer.
* * 2) Redistributions in binary form must reproduce the above copyright
* *    notice, this list of conditions and the following disclaimer in the
* *    documentation and/or other materials provided with the distribution.
* * 3) Neither the name of Huawei nor the names of its contributors may
* *    be used to endorse or promote products derived from this software
* *    without specific prior written permission.
*
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "RnicDebug.h"


/*****************************************************************************
  2 外部函数声明
*****************************************************************************/


/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
******************************************************************************/

RNIC_MNTN_STATS_STRU                    g_stRnicMntnStats = {0};
RNIC_STATS_INFO_STRU                    g_astRnicStats[RNIC_NET_ID_MAX_NUM];
VOS_UINT32                              g_ulRnicPrintUlDataFlg = VOS_FALSE;
VOS_UINT32                              g_ulRnicPrintDlDataFlg = VOS_FALSE;


/******************************************************************************
   5 函数实现
******************************************************************************/

VOS_VOID RNIC_SetPrintUlDataFlg(VOS_UINT32 ulFlg)
{
    g_ulRnicPrintUlDataFlg = ulFlg;
}


VOS_VOID RNIC_ShowRnicPdpStats(VOS_UINT8 ucRmNetId)
{
    RNIC_PDP_CTX_STRU                  *pstPdpCtx;

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowRnicPdpStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    pstPdpCtx                           = RNIC_GetPdpCtxAddr(ucRmNetId);

    PS_PRINTF("RNIC %d IPV4 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV4 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV4 PDP IPV4ADDR                   %d\n\n", ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ulIpv4Addr);

    PS_PRINTF("RNIC %d IPV6 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV6 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV6 PDP IPV6ADDR                   %s\n\n", ucRmNetId, pstPdpCtx->stIpv6PdpInfo.aucIpv6Addr);

    PS_PRINTF("RNIC %d IPV4V6 PDP STATUS                   %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV4V6 PDP RABID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV4V6 PDP IPV4ADDR                 %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ulIpv4Addr);
    PS_PRINTF("RNIC %d IPV4V6 PDP IPV6ADDR                 %s\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.aucIpv6Addr);
}


VOS_VOID RNIC_ShowULProcStats(VOS_UINT8 ucRmNetId)
{
    PS_PRINTF("NET TX RMNETID ERR NUM                                 %d\n", g_stRnicMntnStats.ulNetTxRmNetIdErrNum);
    PS_PRINTF("SPE TX PORTID ERR NUM                                  %d\n", g_stRnicMntnStats.ulSpeTxPortIdErrNum);

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowUlProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* 上行统计量 */
    PS_PRINTF("RNIC %d流控状态                                        %d\n", ucRmNetId, g_stRnicCtx.astSpecCtx[ucRmNetId].enFlowCtrlStatus);
    PS_PRINTF("RNIC %d收到上行IPV4数据的个数                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4PktNum);
    PS_PRINTF("RNIC %d收到上行IPV6数据的个数                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv6PktNum);
    PS_PRINTF("IPV4V6类型激活时RNIC %d收到上行数据的个数IPV4IPV6      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4v6PktNum);
    PS_PRINTF("RNIC %d未激活时收到上行数据的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvUndiaPktNum);
    PS_PRINTF("RNIC %d上行发送给ADS数据的个数                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktNum);
    PS_PRINTF("RNIC %d调ADS发送上行数据失败的个数                     %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktFailNum);
    PS_PRINTF("RNIC %d未拨上号前上行收到IPV4广播包的个数              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlIpv4BrdcstPktNum);
    PS_PRINTF("RNIC %d上行转换为IMM_ZC失败的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlImmzcFailPktNum);
    PS_PRINTF("RNIC %d上行去除MAC头失败的个数                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRmvMacHdrFailPktNum);
    PS_PRINTF("RNIC %d网卡私有数据错误丢掉上行数据包的个数            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetCardDiscardNum);
    PS_PRINTF("RNIC %d网卡ID错误丢掉上行数据包的个数                  %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetIdDiscardNum);
    PS_PRINTF("RNIC %dModem ID错误丢掉上行数据包的个数                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlModemIdDiscardNum);
    PS_PRINTF("RNIC %d流控丢掉上行数据包的个数                        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlFlowCtrlDiscardNum);
    PS_PRINTF("RNIC %d收到错误数据包的个数非ipv4ipv6包                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvErrPktNum);
    PS_PRINTF("RNIC %d成功上报APP按需拨号                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpSucc);
    PS_PRINTF("RNIC %d上报APP按需拨号失败                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpFail);
    PS_PRINTF("RNIC %d成功上报APP断开拨号                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownSucc);
    PS_PRINTF("RNIC %d上报APP断开拨号失败                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownFail);

    if (RNIC_RMNET_ID_0 == ucRmNetId)
    {
        PS_PRINTF("拨号模式                                           %d\n", g_stRnicCtx.stDialMode.enDialMode);
        PS_PRINTF("按需拨号是否上报事件                               %d\n", g_stRnicCtx.stDialMode.enEventReportFlag);
        PS_PRINTF("按需拨号断开时间                                   %d\n", g_stRnicCtx.stDialMode.ulIdleTime);
    }

    PS_PRINTF("RNIC %d RAB ID错误，RNIC丢弃的数据包个数                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRabIdErr);
    PS_PRINTF("RNIC %d PDN ID错误，RNIC丢弃的数据包个数                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlPdnIdErr);

    PS_PRINTF("\r\n");

    return;
}


VOS_VOID RNIC_ShowDLProcStats(VOS_UINT8 ucRmNetId)
{
    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowDLProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* 下行统计量 */
    PS_PRINTF("RNIC %d收到下行IPV4数据的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv4PktNum);
    PS_PRINTF("RNIC %d收到下行IPV6数据的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv6PktNum);
    PS_PRINTF("RNIC %d发送下行数据的个数                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktNum);
    PS_PRINTF("RNIC %d发送下行数据失败的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktFailNum);
    PS_PRINTF("RNIC %d收到下行数据包大于MTU的个数                 %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvBigPktNum);
    PS_PRINTF("RNIC %d网卡未激活丢弃的数据个数                    %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlDiscardPktNum);
    PS_PRINTF("RNIC %d下行加MAC头失败的个数                       %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlAddMacHdFailNum);
    PS_PRINTF("RNIC %d网卡私有数据错误丢掉下行数据包的个数        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetCardDiscardNum);
    PS_PRINTF("RNIC %d网卡ID错误丢掉下行数据包的个数              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetIdDiscardNum);
#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
    PS_PRINTF("RNIC %d网卡NAPI Netif收到下行数据包的个数          %d\n", ucRmNetId, RNIC_GET_NAPI_NETIF_RCV_PKT_NUM(ucRmNetId));
    PS_PRINTF("RNIC %d网卡NAPI GRO收到下行数据包的个数            %d\n", ucRmNetId, RNIC_GET_NAPI_GRO_RCV_PKT_NUM(ucRmNetId));
#endif
    PS_PRINTF("RNIC %d网卡GRO入队失败主动丢弃下行数据包的个数     %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNapiPollQueDiscardPktNum);
    PS_PRINTF("RNIC 当前NAPI Poll队列长度                         %d\n", g_ulRnicNapiPollQueLen[ucRmNetId]);
    PS_PRINTF("RNIC %d收到错误数据包的个数非ipv4ipv6包            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvErrPktNum);
    PS_PRINTF("\r\n");

    return;
}


VOS_VOID RNIC_ShowResetStats(VOS_VOID)
{
    PS_PRINTF("模块初始化标识                              %d\n", g_astRnicStats[0].ulSemInitFlg);
    PS_PRINTF("当前的二进制信号量                          %u\n", g_stRnicCtx.hResetSem); /*lint !e559 */
    PS_PRINTF("创建的二进制信号量                          %u\n", g_astRnicStats[0].hBinarySemId); /*lint !e559 */
    PS_PRINTF("创建二进制信号量失败次数                    %d\n", g_astRnicStats[0].ulCreateBinarySemFailNum);
    PS_PRINTF("锁二进制信号量失败次数                      %d\n", g_astRnicStats[0].ulLockBinarySemFailNum);
    PS_PRINTF("最后一次锁二进制信号量失败原因              %x\n", g_astRnicStats[0].ulLastBinarySemErrRslt);
    PS_PRINTF("复位成功的次数                              %d\n", g_astRnicStats[0].ulResetSucessNum);
}


VOS_VOID RNIC_ShowImsPortsBindStats(VOS_VOID)
{
    PS_PRINTF("ulImsPortRangeNumErrNum:                    %d\n", g_stRnicMntnStats.ulImsPortRangeNumErrNum);
    PS_PRINTF("ulBindPidWriteLenErrNum:                    %d\n", g_stRnicMntnStats.ulBindPidWriteLenErrNum);
    PS_PRINTF("ulBindPidWriteCpyErrNum:                    %d\n", g_stRnicMntnStats.ulBindPidWriteCpyErrNum);
    PS_PRINTF("ulBindPidWritePidErrNum:                    %d\n", g_stRnicMntnStats.ulBindPidWritePidErrNum);
    PS_PRINTF("ulBindPidReadCpyErrNum :                    %d\n", g_stRnicMntnStats.ulBindPidReadCpyErrNum);
    PS_PRINTF("ulImsSipPortRangeNumErrNum :                %d\n", g_stRnicMntnStats.ulImsSipPortRangeNumErrNum);
    PS_PRINTF("\r\n");
    return;
}

#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)

VOS_VOID RNIC_ShowNapiInfo(VOS_UINT8 ucRmNetId)
{
    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowDLProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    PS_PRINTF("ucNetInterfaceMode     :(0:Net_rx/1:NAPI)       %d\n", g_stRnicCtx.stRnicNetIfCfg.ucNetInterfaceMode);
    PS_PRINTF("enNapiWeightAdjMode    :(0:static/1:dynamic)    %d\n", g_stRnicCtx.stRnicNetIfCfg.enNapiWeightAdjMode);
    PS_PRINTF("ucNapiPollWeight       :                        %d\n", g_stRnicCtx.stRnicNetIfCfg.ucNapiPollWeight);
    PS_PRINTF("usNapiPollQueMaxLen    :                        %d\n", g_stRnicCtx.stRnicNetIfCfg.usNapiPollQueMaxLen);
    PS_PRINTF("Rmnet%d.enNapiRcvIf     :(0:GRO/1:Netif)         %d\n", ucRmNetId,RNIC_GET_NAPI_RCV_IF(ucRmNetId));
    PS_PRINTF("enTetherConnStat       :(0:disconn/1:conn)      %d\n", g_stRnicCtx.stUsbTetherInfo.enTetherConnStat);
    PS_PRINTF("ucMatchRmnetNameFlg    :(0:mismatch/1:match)    %d\n", g_stRnicCtx.stUsbTetherInfo.ucMatchRmnetNameFlg);
    PS_PRINTF("aucRmnetName           :                        %s\n", g_stRnicCtx.stUsbTetherInfo.aucRmnetName);
    PS_PRINTF("\r\n");
    return;
}
#endif


VOS_VOID RNIC_Help(VOS_VOID)
{

    PS_PRINTF("********************RNIC调试信息************************\n");
    PS_PRINTF("RNIC_ShowULProcStats  ucRmNetId                 显示指定RNIC网卡上行统计信息\n");
    PS_PRINTF("RNIC_ShowDLProcStats  ucRmNetId                 显示指定RNIC网卡下行统计信息\n");
    PS_PRINTF("RNIC_ShowRnicPdpStats ucRmNetId                 显示指定RNIC网卡PDP激活信息\n");
    PS_PRINTF("RNIC_ShowResetStats                             显示指定RNIC复位状态信息\n");
    PS_PRINTF("RNIC_ShowImsPortsBindStats                      显示Ims保留端口号绑定的统计信息\n");
#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
    PS_PRINTF("RNIC_ShowNapiInfo     ucRmNetId                 显示指定RNIC网卡的NAPI相关信息\n");
#endif

    return;
}


VOS_VOID RNIC_ShowDataFromIpStack(
    struct sk_buff                     *pstSkb
)
{
    VOS_UINT32                          i;

    PS_PRINTF("RNIC_ShowDataFromIpStack: data len is %d. \r\n", pstSkb->len);

    PS_PRINTF("RNIC_ShowDataFromIpStack: data content is: \r\n");

    for (i = 0; i < pstSkb->len; i++)
    {
        if (pstSkb->data[i] > 0xf)
        {
            PS_PRINTF("%x", pstSkb->data[i]);
        }
        else
        {
            PS_PRINTF("0%x", pstSkb->data[i]);
        }
    }

    PS_PRINTF("\r\n");

    return;
}





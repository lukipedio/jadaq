//
// Created by troels on 9/19/17.
//

#include "Digitizer.hpp"
#include "StringConversion.hpp"
#include <regex>
#include <chrono>
#include <thread>

#define MAX_GROUPS 8

#define SET_CASE(D,F,V) \
    case F :            \
        D->set##F(V);   \
        break;

#define GET_CASE(D,F,TS)        \
    case F :                    \
        return TS(D->get##F());

#define SET_ICASE(D,F,C,V)   \
    case F :                 \
        D->set##F(C,V);      \
        break;

#define GET_ICASE(D,F,C,TS)      \
    case F :                     \
        return TS(D->get##F(C));

static void set_(caen::Digitizer* digitizer, FunctionID functionID, const std::string& value)
{
    switch(functionID)
    {
        SET_CASE(digitizer,MaxNumEventsBLT,s2ui(value))
        SET_CASE(digitizer,ChannelEnableMask,bs2ui(value))
        SET_CASE(digitizer,GroupEnableMask,bs2ui(value))
        SET_CASE(digitizer,DecimationFactor,s2ui(value))
        SET_CASE(digitizer,PostTriggerSize,s2ui(value))
        SET_CASE(digitizer,IOlevel,s2iol(value))
        SET_CASE(digitizer,AcquisitionMode,s2am(value))
        SET_CASE(digitizer,ExternalTriggerMode,s2tm(value))
        SET_CASE(digitizer,SWTriggerMode,s2tm(value))
        SET_CASE(digitizer,RunSynchronizationMode,s2rsm(value))
        SET_CASE(digitizer,OutputSignalMode,s2osm(value))
        SET_CASE(digitizer,DESMode,s2ed(value))
        SET_CASE(digitizer,ZeroSuppressionMode,s2zsm(value))
        SET_CASE(digitizer,AnalogMonOutput,s2amom(value))
        SET_CASE(digitizer,AnalogInspectionMonParams,s2aimp(value))
        SET_CASE(digitizer,EventPackaging,s2ed(value))
        SET_CASE(digitizer,FastTriggerDigitizing,s2ed(value))
        SET_CASE(digitizer,FastTriggerMode,s2tm(value))
        SET_CASE(digitizer,DRS4SamplingFrequency,s2drsff(value))
        SET_CASE(digitizer,DPPAcquisitionMode,s2cdam(value))
        SET_CASE(digitizer,DPPTriggerMode,s2dtm(value))
        SET_CASE(digitizer,MaxNumAggregatesBLT,s2ui(value))
        SET_CASE(digitizer,RunDelay,s2ui(value))
        SET_CASE(digitizer,SAMCorrectionLevel,s2samcl(value))
        SET_CASE(digitizer,SAMSamplingFrequency,s2samf(value))
        SET_CASE(digitizer,SAMAcquisitionMode,s2samam(value))
        SET_CASE(digitizer,TriggerLogic,s2tlp(value))
        SET_CASE(digitizer,BoardConfiguration,s2ui(value))
        SET_CASE(digitizer,EasyBoardConfiguration,s2ebc(value))
        SET_CASE(digitizer,AggregateOrganization,s2ui(value))
        SET_CASE(digitizer,AcquisitionControl,s2ui(value))
        SET_CASE(digitizer,EasyAcquisitionControl,s2eac(value))
        SET_CASE(digitizer,RecordLength,s2ui(value))
        SET_CASE(digitizer,NumEventsPerAggregate,s2ui(value))
        SET_CASE(digitizer,GateWidth,s2ui(value))
        SET_CASE(digitizer,GateOffset,s2ui(value))
        SET_CASE(digitizer,FixedBaseline,s2ui(value))
        SET_CASE(digitizer,DPPAlgorithmControl,s2ui(value))
        SET_CASE(digitizer,EasyDPPAlgorithmControl,s2edppac(value))
        SET_CASE(digitizer,TriggerHoldOffWidth,s2ui(value))
        SET_CASE(digitizer,ShapedTriggerWidth,s2ui(value))
        default:
            throw std::invalid_argument{"Unknown Function"};

    }
}

static void set_(caen::Digitizer* digitizer, FunctionID functionID, int index, const std::string& value) {
    switch (functionID) {
        SET_ICASE(digitizer,ChannelDCOffset,index,s2ui(value))
        SET_ICASE(digitizer,GroupDCOffset,index,s2ui(value))
        SET_ICASE(digitizer,ChannelSelfTrigger,index,s2tm(value))
        SET_ICASE(digitizer,GroupSelfTrigger,index,s2tm(value))
        SET_ICASE(digitizer,ChannelTriggerThreshold,index,s2ui(value))
        SET_ICASE(digitizer,GroupTriggerThreshold,index,s2ui(value))
        SET_ICASE(digitizer,ChannelGroupMask,index,s2ui(value))
        SET_ICASE(digitizer,TriggerPolarity,index,s2tp(value))
        SET_ICASE(digitizer,GroupFastTriggerThreshold,index,s2ui(value))
        SET_ICASE(digitizer,GroupFastTriggerDCOffset,index,s2ui(value))
        SET_ICASE(digitizer,ChannelZSParams,index,s2zsp(value))
        SET_ICASE(digitizer,SAMPostTriggerSize,index,s2i(value))
        SET_ICASE(digitizer,SAMTriggerCountVetoParam,index,s2samtcvp(value))
        SET_ICASE(digitizer,DPPPreTriggerSize,index,s2ui(value))
        SET_ICASE(digitizer,ChannelPulsePolarity,index,s2pp(value))
        SET_ICASE(digitizer,RecordLength,index,s2ui(value))
        SET_ICASE(digitizer,NumEventsPerAggregate,index,s2ui(value))
        SET_ICASE(digitizer,GateWidth,index,s2ui(value))
        SET_ICASE(digitizer,GateOffset,index,s2ui(value))
        SET_ICASE(digitizer,FixedBaseline,index,s2ui(value))
        SET_ICASE(digitizer,DPPAlgorithmControl,index,s2ui(value))
        SET_ICASE(digitizer,EasyDPPAlgorithmControl,index,s2edppac(value))
        SET_ICASE(digitizer,TriggerHoldOffWidth,index,s2ui(value))
        SET_ICASE(digitizer,ShapedTriggerWidth,index,s2ui(value))
        default:
            throw std::invalid_argument{"Unknown Function"};
    }
}

static std::string get_(caen::Digitizer* digitizer, FunctionID functionID)
{
    switch(functionID)
    {
        GET_CASE(digitizer,MaxNumEventsBLT,to_string)
        GET_CASE(digitizer,ChannelEnableMask,bin_string)
        GET_CASE(digitizer,GroupEnableMask,bin_string<MAX_GROUPS>)
        GET_CASE(digitizer,DecimationFactor,to_string)
        GET_CASE(digitizer,PostTriggerSize,to_string)
        GET_CASE(digitizer,IOlevel,to_string)
        GET_CASE(digitizer,AcquisitionMode,to_string)
        GET_CASE(digitizer,ExternalTriggerMode,to_string)
        GET_CASE(digitizer,SWTriggerMode,to_string)
        GET_CASE(digitizer,RunSynchronizationMode,to_string)
        GET_CASE(digitizer,OutputSignalMode,to_string)
        GET_CASE(digitizer,DESMode,to_string)
        GET_CASE(digitizer,ZeroSuppressionMode,to_string)
        GET_CASE(digitizer,AnalogMonOutput,to_string)
        GET_CASE(digitizer,AnalogInspectionMonParams,to_string)
        GET_CASE(digitizer,EventPackaging,to_string)
        GET_CASE(digitizer,FastTriggerDigitizing,to_string)
        GET_CASE(digitizer,FastTriggerMode,to_string)
        GET_CASE(digitizer,DRS4SamplingFrequency,to_string)
        GET_CASE(digitizer,DPPAcquisitionMode,to_string)
        GET_CASE(digitizer,DPPTriggerMode,to_string)
        GET_CASE(digitizer,MaxNumAggregatesBLT,to_string)
        GET_CASE(digitizer,RunDelay,to_string)
        GET_CASE(digitizer,SAMCorrectionLevel,to_string)
        GET_CASE(digitizer,SAMSamplingFrequency,to_string)
        GET_CASE(digitizer,SAMAcquisitionMode,to_string)
        GET_CASE(digitizer,TriggerLogic,to_string)
        GET_CASE(digitizer,BoardConfiguration,to_string)
        GET_CASE(digitizer,EasyBoardConfiguration,to_string)
        GET_CASE(digitizer,AggregateOrganization,to_string)
        GET_CASE(digitizer,AcquisitionControl,to_string)
        GET_CASE(digitizer,EasyAcquisitionControl,to_string)
        GET_CASE(digitizer,AcquisitionStatus,to_string)
        GET_CASE(digitizer,EasyAcquisitionStatus,to_string)
        GET_CASE(digitizer,RecordLength,to_string)
        GET_CASE(digitizer,NumEventsPerAggregate,to_string)
        default:
            throw std::invalid_argument{"Unknown Function"};

    }
}

static std::string get_(caen::Digitizer* digitizer, FunctionID functionID, int index)
{

    switch (functionID) {
        GET_ICASE(digitizer,ChannelDCOffset,index,to_string)
        GET_ICASE(digitizer,GroupDCOffset,index,to_string)
        GET_ICASE(digitizer,ChannelSelfTrigger,index,to_string)
        GET_ICASE(digitizer,GroupSelfTrigger,index,to_string)
        GET_ICASE(digitizer,ChannelTriggerThreshold,index,to_string)
        GET_ICASE(digitizer,GroupTriggerThreshold,index,to_string)
        GET_ICASE(digitizer,ChannelGroupMask,index,to_string)
        GET_ICASE(digitizer,TriggerPolarity,index,to_string)
        GET_ICASE(digitizer,GroupFastTriggerThreshold,index,to_string)
        GET_ICASE(digitizer,GroupFastTriggerDCOffset,index,to_string)
        GET_ICASE(digitizer,ChannelZSParams,index,to_string)
        GET_ICASE(digitizer,SAMPostTriggerSize,index,to_string)
        GET_ICASE(digitizer,SAMTriggerCountVetoParam,index,to_string)
        GET_ICASE(digitizer,DPPPreTriggerSize,index,to_string)
        GET_ICASE(digitizer,ChannelPulsePolarity,index,to_string)
        GET_ICASE(digitizer,RecordLength,index,to_string)
        GET_ICASE(digitizer,NumEventsPerAggregate,index,to_string)
        GET_ICASE(digitizer,GateWidth,index,to_string)
        GET_ICASE(digitizer,GateOffset,index,to_string)
        GET_ICASE(digitizer,FixedBaseline,index,to_string)
        GET_ICASE(digitizer,DPPAlgorithmControl,index,to_string)
        GET_ICASE(digitizer,EasyDPPAlgorithmControl,index,to_string)
        GET_ICASE(digitizer,TriggerHoldOffWidth,index,to_string)
        GET_ICASE(digitizer,ShapedTriggerWidth,index,to_string)
        default:
            throw std::invalid_argument{"Unknown Function"};
    }
}

template <typename R, typename F>
static R backOffRepeat(F fun, int retry=3,  std::chrono::milliseconds grace=std::chrono::milliseconds(1))
{
    while (true) {
        try {
            return fun();
        }
        catch (caen::Error &e) {
            if (e.code() == CAEN_DGTZ_CommError && retry-- > 0) {
                std::this_thread::sleep_for(grace);
                grace *= 10;
            } else throw;
        }
    }
}

std::string Digitizer::get(FunctionID functionID, int index)
{
    return backOffRepeat<std::string>([this,&functionID,&index](){ return get_(digitizer,functionID,index); });
}

std::string Digitizer::get(FunctionID functionID)
{
    return backOffRepeat<std::string>([this,&functionID](){ return get_(digitizer,functionID); });
}

void Digitizer::set(FunctionID functionID, int index, std::string value)
{
    return backOffRepeat<void>([this,&functionID,&index,&value](){ return set_(digitizer,functionID,index,value); });
}

void Digitizer::set(FunctionID functionID, std::string value)
{
    return backOffRepeat<void>([this,&functionID,&value](){ return set_(digitizer,functionID,value); });
}

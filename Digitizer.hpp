//
// Created by troels on 9/19/17.
//

#ifndef JADAQ_DIGITIZER_HPP
#define JADAQ_DIGITIZER_HPP

#include <string>
#include <unordered_map>

#include "caen.hpp"
enum FunctionID {
    // Global i.e. no channel/group
    MaxNumEventsBLT,
    ChannelEnableMask,
    GroupEnableMask,
    DecimationFactor,
    PostTriggerSize,
    IOlevel,
    AcquisitionMode,
    ExternalTriggerMode,
    SWTriggerMode,
    RunSynchronizationMode,
    OutputSignalMode,
    DESMode,
    DPPAcquisitionMode,
    DPPTriggerMode,
    // Channel/group setting
    ChannelDCOffset,
    GroupDCOffset,
    ChannelSelfTrigger,
    GroupSelfTrigger,
    ChannelTriggerThreshold,
    GroupTriggerThreshold,
    ChannelGroupMask,
    TriggerPolarity,
    DPPPreTriggerSize,
    ChannelPulsePolarity,
    // Channel/group optional
    RecordLength,
    NumEventsPerAggregate
};

class Digitizer
{
private:
    caen::Digitizer* digitizer;
public:
    Digitizer(caen::Digitizer* digitizer_) : digitizer(digitizer_) {}
    const std::string name() { return digitizer->modelName() + "_" + std::to_string(digitizer->serialNumber()); }
    void set(FunctionID functionID, std::string value);
    void set(FunctionID functionID, int index, std::string value);
    std::string get(FunctionID functionID);
    std::string get(FunctionID functionID, int index);
    static FunctionID functionID(std::string s);
    static const char* functionName(FunctionID id);
    static bool needIndex(FunctionID id) { return id >= ChannelDCOffset; }

};


#endif //JADAQ_DIGITIZER_HPP
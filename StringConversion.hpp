/**
 * jadaq (Just Another DAQ)
 * Copyright (C) 2017  Troels Blum <troels@blum.dk>
 * Contributions from  Jonas Bardino <bardino@nbi.ku.dk>
 *
 * @file
 * @author Troels Blum <troels@blum.dk>
 * @section LICENSE
 * This program is free software: you can redistribute it and/or modify
 *        it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 *         but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 * Convert between strings and various digitizer helper types.
 *
 */

#ifndef JADAQ_STRINGCONVERSION_HPP
#define JADAQ_STRINGCONVERSION_HPP

#include <string>
#include <sstream>
#include <bitset>
#include <climits>
#include "caen.hpp"

using std::to_string;

/* force small integers to full unsigned int for proper printing */
template<typename T>
std::string ui_to_string(T v)
{
    std::stringstream ss;
    ss << unsigned(v);
    return ss.str();
}

template<typename T>
std::string hex_string(T v)
{
    std::stringstream ss;
    ss << "0x" << std::hex << v;
    return ss.str();
}

template<typename T>
std::string oct_string(T v)
{
    std::stringstream ss;
    ss << '0' << std::oct << v;
    return ss.str();
}

template<size_t w=0, typename T>
std::string bin_string(T v)
{
    std::bitset<w?w:(sizeof(T)*CHAR_BIT)> bs(v);
    return bs.to_string();
}
// binary string
unsigned int bs2ui(const std::string& s);
int s2i(const std::string& s);
unsigned int s2ui(const std::string& s);
uint16_t s2ui16(const std::string& s);
uint8_t s2ui8(const std::string& s);
CAEN_DGTZ_IOLevel_t s2iol(const std::string& s);
CAEN_DGTZ_AcqMode_t s2am(const std::string& s);
CAEN_DGTZ_TriggerMode_t s2tm(const std::string& s);
CAEN_DGTZ_DPP_TriggerMode_t s2dtm(const std::string& s);
CAEN_DGTZ_DRS4Frequency_t s2drsff(const std::string& s);
CAEN_DGTZ_RunSyncMode_t s2rsm(const std::string& s);
CAEN_DGTZ_OutputSignalMode_t s2osm(const std::string& s);
CAEN_DGTZ_EnaDis_t s2ed(const std::string& s);
CAEN_DGTZ_ZS_Mode_t s2zsm(const std::string& s);
CAEN_DGTZ_AnalogMonitorOutputMode_t s2amom(const std::string& s);
CAEN_DGTZ_AnalogMonitorMagnify_t s2mf(const std::string& s);
CAEN_DGTZ_AnalogMonitorInspectorInverter_t s2ami(const std::string& s);
CAEN_DGTZ_TriggerPolarity_t s2tp(const std::string& s);
CAEN_DGTZ_PulsePolarity_t s2pp(const std::string& s);

std::string to_string(const caen::ZSParams &zsp);
caen::ZSParams s2zsp(const std::string& s);
std::string to_string(const caen::AIMParams &aimp);
caen::AIMParams s2aimp(const std::string& s);
std::string to_string(const caen::ChannelPairTriggerLogicParams &cptlp);
caen::ChannelPairTriggerLogicParams s2cptlp(const std::string& s);
std::string to_string(const caen::TriggerLogicParams &tlp);
caen::TriggerLogicParams s2tlp(const std::string& s);
std::string to_string(const caen::SAMTriggerCountVetoParams &samtcvp);
caen::SAMTriggerCountVetoParams s2samtcvp(const std::string& s);
std::string to_string(const caen::EasyDPPAlgorithmControlHelper &edppach);
caen::EasyDPPAlgorithmControlHelper s2edppach(const std::string& s);
std::string to_string(const caen::EasyBoardConfigurationHelper &ebch);
caen::EasyBoardConfigurationHelper s2ebch(const std::string& s);
std::string to_string(const caen::EasyDPPBoardConfigurationHelper &edbch);
caen::EasyDPPBoardConfigurationHelper s2edbch(const std::string& s);
std::string to_string(const caen::EasyAcquisitionControlHelper &each);
caen::EasyAcquisitionControlHelper s2each(const std::string& s);
std::string to_string(const caen::EasyDPPAcquisitionControlHelper &edach);
caen::EasyDPPAcquisitionControlHelper s2edach(const std::string& s);
std::string to_string(const caen::EasyAcquisitionStatusHelper &eash);
caen::EasyAcquisitionStatusHelper s2eash(const std::string& s);
std::string to_string(const caen::EasyDPPAcquisitionStatusHelper &edash);
caen::EasyDPPAcquisitionStatusHelper s2edash(const std::string& s);
std::string to_string(const caen::EasyGlobalTriggerMaskHelper &egtmh);
caen::EasyGlobalTriggerMaskHelper s2egtmh(const std::string& s);
std::string to_string(const caen::EasyDPPGlobalTriggerMaskHelper &edgtmh);
caen::EasyDPPGlobalTriggerMaskHelper s2edgtmh(const std::string& s);
std::string to_string(const caen::EasyFrontPanelTRGOUTEnableMaskHelper &efptoemh);
caen::EasyFrontPanelTRGOUTEnableMaskHelper s2efptoemh(const std::string& s);
std::string to_string(const caen::EasyDPPFrontPanelTRGOUTEnableMaskHelper &edfptoemh);
caen::EasyDPPFrontPanelTRGOUTEnableMaskHelper s2edfptoemh(const std::string& s);
std::string to_string(const caen::EasyFrontPanelIOControlHelper &efpioch);
caen::EasyFrontPanelIOControlHelper s2efpioch(const std::string& s);
std::string to_string(const caen::EasyDPPFrontPanelIOControlHelper &edfpioch);
caen::EasyDPPFrontPanelIOControlHelper s2edfpioch(const std::string& s);
std::string to_string(const caen::EasyROCFPGAFirmwareRevisionHelper &erffrh);
caen::EasyROCFPGAFirmwareRevisionHelper s2erffrh(const std::string& s);
std::string to_string(const caen::EasyDPPROCFPGAFirmwareRevisionHelper &edrffrh);
caen::EasyDPPROCFPGAFirmwareRevisionHelper s2edrffrh(const std::string& s);
std::string to_string(const caen::EasyFanSpeedControlHelper &efsch);
caen::EasyFanSpeedControlHelper s2efsch(const std::string& s);
std::string to_string(const caen::EasyDPPFanSpeedControlHelper &edfsch);
caen::EasyDPPFanSpeedControlHelper s2edfsch(const std::string& s);
std::string to_string(const caen::EasyReadoutControlHelper &erch);
caen::EasyReadoutControlHelper s2erch(const std::string& s);
std::string to_string(const caen::EasyDPPReadoutControlHelper &edrch);
caen::EasyDPPReadoutControlHelper s2edrch(const std::string& s);
std::string to_string(const caen::EasyReadoutStatusHelper &ersh);
caen::EasyReadoutStatusHelper s2ersh(const std::string& s);
std::string to_string(const caen::EasyDPPReadoutStatusHelper &edrsh);
caen::EasyDPPReadoutStatusHelper s2edrsh(const std::string& s);
std::string to_string(const caen::EasyAMCFirmwareRevisionHelper &eafrh);
caen::EasyAMCFirmwareRevisionHelper s2eafrh(const std::string& s);
std::string to_string(const caen::EasyDPPAMCFirmwareRevisionHelper &edafrh);
caen::EasyDPPAMCFirmwareRevisionHelper s2edafrh(const std::string& s);

std::string to_string(CAEN_DGTZ_DPP_AcqMode_t mode);
CAEN_DGTZ_DPP_AcqMode_t s2dam(const std::string& s);
std::string to_string(CAEN_DGTZ_DPP_SaveParam_t sp);
CAEN_DGTZ_DPP_SaveParam_t s2sp(const std::string& s);
std::string to_string(const caen::DPPAcquisitionMode &dam);
caen::DPPAcquisitionMode s2cdam(const std::string& s);
std::string to_string(CAEN_DGTZ_SAM_CORRECTION_LEVEL_t level);
CAEN_DGTZ_SAM_CORRECTION_LEVEL_t s2samcl(const std::string& s);
std::string to_string(CAEN_DGTZ_SAMFrequency_t frequency);
CAEN_DGTZ_SAMFrequency_t s2samf(const std::string& s);
std::string to_string(CAEN_DGTZ_AcquisitionMode_t mode);
CAEN_DGTZ_AcquisitionMode_t s2samam(const std::string& s);


#endif //JADAQ_STRINGCONVERSION_HPP

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
 * Digitizer access, used to get/set configuration values and to
 * do actual acquisition.
 *
 */

#ifndef JADAQ_DIGITIZER_HPP
#define JADAQ_DIGITIZER_HPP

#include "FunctionID.hpp"
#include "caen.hpp"

#include <string>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <fstream>
#include "trace.hpp"
#include "DataFormat.hpp"

using boost::asio::ip::udp;

struct CommHelper {
    boost::asio::io_service sendIOService;
    udp::endpoint remoteEndpoint;
    udp::socket *socket = nullptr;
    /* NOTE: use a static buffer of MAXBUFSIZE bytes for sending */
    char sendBuf[MAXBUFSIZE];
    Data::EventData *eventData = nullptr;
    Data::Meta *metadata= nullptr;
    Data::PackedEvents packedEvents;
};


class Digitizer
{
public:
    STAT(struct Stats {
             uint32_t bytesRead = 0;
             uint32_t eventsFound = 0;
             uint32_t eventsUnpacked = 0;
             uint32_t eventsDecoded = 0;
             uint32_t eventsSent = 0;
         };)

private:
    caen::Digitizer* digitizer;
    CAEN_DGTZ_DPPFirmware_t firmware;
    uint32_t boardConfiguration = 0;
    bool waveformRecording = false;
    bool dump=false;
    std::fstream* dumpfile = nullptr;

    uint32_t throttleDownMSecs = 0;
    /* We bind a ReadoutBuffer to each digitizer for ease of use */
    caen::ReadoutBuffer readoutBuffer_;
    /* Standard firmware uses eventInfo and Event while DPP firmware
     * keeps it all in a DPPEvents structure. */
    caen::EventInfo eventInfo_;
    void *plainEvent = nullptr;
    caen::DPPEvents events_;
    caen::DPPWaveforms waveforms;

    STAT(Stats stats_;)

    /* Per-digitizer communication helpers */
    void extractPlainEvents();
    void extractDPPEvents();

public:
    /* Connection parameters */
    const CAEN_DGTZ_ConnectionType linkType;
    const int linkNum;
    const int conetNode;
    const uint32_t VMEBaseAddress;

    Digitizer(CAEN_DGTZ_ConnectionType linkType_, int linkNum_, int conetNode_, uint32_t VMEBaseAddress_);
    //~Digitizer();
    void close();
    const std::string name() { return digitizer->modelName() + "_" + std::to_string(digitizer->serialNumber()); }
    const std::string model() { return digitizer->modelName(); }
    const std::string serial() { return std::to_string(digitizer->serialNumber()); }
    uint32_t channels() {return digitizer->channels();}

    void set(FunctionID functionID, std::string value);
    void set(FunctionID functionID, int index, std::string value);
    std::string get(FunctionID functionID);
    std::string get(FunctionID functionID, int index);

    void acquisition();
    const Stats& stats() const {return stats_;}
    //Post setup, pre aquisition initialization
    void initialize(bool dump_=false);

    // TODO make CommHelper private
    CommHelper* commHelper;

    // TODO Sould we do somthing different than expose there three function?
    void startAcquisition() { digitizer->startAcquisition(); }
    void stopAcquisition() { digitizer->stopAcquisition(); }
    void reset() { digitizer->reset(); }
};


#endif //JADAQ_DIGITIZER_HPP

//
// Created by troels on 6/27/18.
//

#ifndef JADAQ_WAVEFORM_HPP
#define JADAQ_WAVEFORM_HPP

#include <cstdint>
#include <ostream>
#include <H5Cpp.h>
#include <iomanip>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define PRINTD(V) std::setw(MAX(sizeof(V)*3,sizeof(#V))) << V
#define PRINTH(V) std::setw(MAX(sizeof(V)*3,sizeof(#V))) << (#V)

struct __attribute__ ((__packed__)) Interval
    {
        uint16_t start;
        uint16_t end;
        void printOn(std::ostream& os) const
        {
            os << PRINTD(start) << " " << PRINTD(end);
        }
        static void insertMembers(H5::CompType& datatype)
        {
            datatype.insertMember("start", HOFFSET(Interval, start), H5::PredType::NATIVE_UINT16);
            datatype.insertMember("end", HOFFSET(Interval, end), H5::PredType::NATIVE_UINT16);
        }
        static size_t size() { return sizeof(Interval); }
        static H5::CompType h5type()
        {
            H5::CompType datatype(size());
            insertMembers(datatype);
            return datatype;
        }
    };

static inline std::ostream& operator<< (std::ostream& os, const Interval& i)
{ i.printOn(os); return os; }

    struct __attribute__ ((__packed__)) Waveform
    {
        uint16_t num_samples;
        uint16_t trigger;
        Interval gate;
        Interval holdoff;
        Interval overthreshold;
        uint16_t samples[];
        void printOn(std::ostream& os) const
        {
            os << PRINTD(num_samples) << " " << PRINTD(trigger) << " " << PRINTD(gate) << " " <<
               PRINTD(holdoff) << " " << PRINTD(overthreshold);
            for (uint16_t i = 0; i < num_samples; ++i)
            {
                os << " " <<  std::setw(5) << samples[i];
            }
        }
        static void headerOn(std::ostream& os)
        {
            os << PRINTH(num_samples) << " " << PRINTH(trigger) << " " << PRINTH(gate) << " " << PRINTH(holdoff) <<
               PRINTH(overthreshold) << " " << "samples";
        }
        void insertMembers(H5::CompType& datatype) const
        {
            datatype.insertMember("num_samples", HOFFSET(Waveform, num_samples), H5::PredType::NATIVE_UINT16);
            datatype.insertMember("trigger", HOFFSET(Waveform, trigger), H5::PredType::NATIVE_UINT16);
            datatype.insertMember("gate", HOFFSET(Waveform, gate), Interval::h5type());
            datatype.insertMember("holdoff", HOFFSET(Waveform, holdoff), Interval::h5type());
            datatype.insertMember("overthreshold", HOFFSET(Waveform, overthreshold), Interval::h5type());
            datatype.insertMember("overthreshold", HOFFSET(Waveform, overthreshold), Interval::h5type());
            static const hsize_t n[1] = {num_samples};
            datatype.insertMember("samples", HOFFSET(Waveform, samples), H5::ArrayType(H5::PredType::NATIVE_UINT16,1,n));
        }
        size_t size() const { return sizeof(Waveform) + sizeof(uint16_t)*num_samples; }

        H5::CompType h5type() const
        {
            H5::CompType datatype(size());
            insertMembers(datatype);
            return datatype;
        }
    };

static inline std::ostream& operator<< (std::ostream& os, const Waveform& w)
{ w.printOn(os); return os; }

#endif //JADAQ_WAVEFORM_HPP
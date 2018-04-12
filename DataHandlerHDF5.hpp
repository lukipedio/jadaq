/**
 * jadaq (Just Another DAQ)
 * Copyright (C) 2018  Troels Blum <troels@blum.dk>
 *
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
 * Write data to HDF5 file
 *
 */

#ifndef JADAQ_DATAHANDLERHDF5_HPP
#define JADAQ_DATAHANDLERHDF5_HPP

#include <string>
#include <H5Cpp.h>
#include "DataHandler.hpp"

class DataHandlerHDF5: public DataHandler
{
public:
    DataHandlerHDF5(std::string fileName);
    ~DataHandlerHDF5();
private:
    H5::H5File* file = nullptr;
};


#endif //JADAQ_DATAHANDLERHDF5_HPP
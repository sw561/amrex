#include <iostream>
#include <string>
#include <cstring>

#include "AMReX.H"
#include "AMReX_Print.H"
#include "AMReX_FPC.H"
#include "AMReX_FabConv.H"
#include "AMReX_Vector.H"
#include "AMReX_IntConv.H"

using namespace amrex;

void writeRealData(const Real* data, std::size_t size, std::ostream& os)
{
    return;
}

void readRealData(Real* data, std::size_t size, std::istream& is,
                  const RealDescriptor& rd)
{
    return;
}

void testIntIO(const IntDescriptor& id_out) {

    std::string data_file_name   = "int_data.dat";
    std::string header_file_name = "int_header_H";
    
    amrex::Vector<int> idata_out;
    for (int i = -99; i <= 100; ++i) {
        idata_out.push_back(i);
    }
    
    std::ofstream ofs;
    ofs.open(data_file_name.c_str(), std::ios::out|std::ios::binary);
    writeIntData(idata_out.data(), idata_out.size(), ofs, id_out);
    ofs.close();
    
    ofs.open(header_file_name.c_str(), std::ios::out);
    ofs << id_out << "\n";
    ofs.close();
    
    IntDescriptor id_in;
    std::ifstream ifs;
    ifs.open(header_file_name.c_str(), std::ios::in);
    ifs >> id_in;
    ifs.close();
    
    AMREX_ALWAYS_ASSERT(id_out == id_in);
    
    amrex::Vector<int> idata_in(idata_out.size());
    ifs.open(data_file_name.c_str(), std::ios::in|std::ios::binary);
    readIntData(idata_in.data(), idata_in.size(), ifs, id_in);
    ifs.close();
    
    for (int i = 0; i < static_cast<int>(idata_in.size()); ++i) {
        AMREX_ALWAYS_ASSERT(idata_in[i] == idata_out[i]);
    }
}

void testLongIO(const IntDescriptor& id_out) {

    std::string data_file_name   = "long_data.dat";
    std::string header_file_name = "long_header_H";
    
    amrex::Vector<long> idata_out;
    for (int i = -99; i <= 100; ++i) {
        idata_out.push_back(i);
    }

    std::ofstream ofs;
    ofs.open(data_file_name.c_str(), std::ios::out|std::ios::binary);
    writeLongData(idata_out.data(), idata_out.size(), ofs, id_out);
    ofs.close();
    
    ofs.open(header_file_name.c_str(), std::ios::out);
    ofs << id_out << "\n";
    ofs.close();
    
    IntDescriptor id_in;
    std::ifstream ifs;
    ifs.open(header_file_name.c_str(), std::ios::in);
    ifs >> id_in;
    ifs.close();
    
    AMREX_ALWAYS_ASSERT(id_out == id_in);
    
    amrex::Vector<long> idata_in(idata_out.size());
    ifs.open(data_file_name.c_str(), std::ios::in|std::ios::binary);
    readLongData(idata_in.data(), idata_in.size(), ifs, id_in);
    ifs.close();
    
    for (int i = 0; i < static_cast<int>(idata_in.size()); ++i) {
        AMREX_ALWAYS_ASSERT(idata_in[i] == idata_out[i]);
    }
}

int main(int argc, char* argv[])
{
    amrex::Initialize(argc,argv);
    
    IntDescriptor little16(2, IntDescriptor::ReverseOrder);
    IntDescriptor little32(4, IntDescriptor::ReverseOrder);
    IntDescriptor little64(8, IntDescriptor::ReverseOrder);
    
    IntDescriptor big16(2, IntDescriptor::NormalOrder);
    IntDescriptor big32(4, IntDescriptor::NormalOrder);
    IntDescriptor big64(8, IntDescriptor::NormalOrder);
    
    testIntIO(little16);
    testIntIO(little32);
    testIntIO(little64);
    
    testIntIO(big16);
    testIntIO(big32);
    testIntIO(big64);
    
    testLongIO(little16);
    testLongIO(little32);
    testLongIO(little64);
    
    testLongIO(big16);
    testLongIO(big32);
    testLongIO(big64);

    amrex::Print() << "passed!" << std::endl;
    
    amrex::Finalize();
}

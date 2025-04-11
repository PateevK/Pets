#pragma once
#include <string>



struct Processor_infoblock {
	std::string core_type;
	std::string name; //Intel core i5 13450HX   
	std::string code_name; //`Raptor Lake-HX (Core i5)' 
	std::string package; // Socket 1700 LGA     
	std::string specification; // | `13th Gen Intel(R) Core(TM) i5 - 13450HX' |
	std::string max_tdp;
	std::string max_voltage;
	std::string technology_nm;
	std::string family;
	std::string model;
	std::string stepping;
	std::string ext_family;
	std::string ext_model;
	std::string arch;
	std::string feat_level;
};
// Per core type + General. 
struct Core_infoblock {
	int core_num;
	int core_load;
	int core_speed; //pizdaNahui can't figureout a way to get valid clock values
	int max_core_speed; 
	int multiplier;
	int bus_speed;
	int rated_FSB; // ???
};
// CPU-Z like style.   
// Linesize & associativity should be per cope type.
struct Cache_infoblock {
	std::string core_type;

	int  l1_cache_size_kb;
	int  l1_cache_instances;
	int  l1_cacheline_size_bytes;
	int  l1_cache_associativity;
	
	int  l2_cache_size_kb;
	int  l2_cache_instances;
	int  l2_cacheline_size_bytes;
	int  l2_cache_associativity;
	
	int  l3_cache_size_kb;
	int  l3_cache_instances;
	int  l3_cacheline_size_bytes;
	int  l3_cache_associativity;
	
	int  l4_cache_size_kb;
	int  l4_cache_instances;
	int  l4_cacheline_size_bytes;
	int  l4_cache_associativity;
};

struct TypeNum{
	std::string type = {};
	int num = 0;
};

struct Footer_infoblock {
	int tot_num_processors; // Don't need it for now.
	int tot_num_cores;
	int tot_num_logical; //threads.
	std::vector<TypeNum> vec_type_num; //total cores 6P + 4E
};
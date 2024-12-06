#include "inst_operation.hpp"
#include <algorithm>

namespace ev{

int EVOper::getOper(int oper){
    if (oper < 256 && config.find(oper) != config.end()){
        return config[oper];
    }
    return oper;
}

EVFile::EVFileStatus EVOper::loadConfig(){
    if (instList.size() == 0){
        return EVFile::EVFileStatus::EVFILE_READ_FAIL;
    }

    for (auto& inst : instList){
        std::string key = inst.substr(0, inst.find(":"));
        std::string value = inst.substr(inst.find(":") + 1);

        if (key.size() == 0 || value.size() == 0 || key[0] == '#'){
            continue;
        }

        if (key[0] < 256 && value[0] < 256){
            config[key[0]] = value[0];
        }
    }
    return EVFile::EVFileStatus::EVFILE_OK;
}

} // namespace ev
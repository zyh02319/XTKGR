//用于增删改查model的控制器
#include "ModelManageController.h"
#include <iostream>


//干扰机模型方法
bool ModelManageController::createJammerModel(const JammerModel& model) {
    std::cout << "[ModelManageController] createJammerModel called for: " << model.name << std::endl;
    bool result = JammerModelDAO::insert(model);
    if (!result) {
        std::cerr << "CreateJammerModel failed for: " << model.name << std::endl;
    }
    return result;
}


bool ModelManageController::updateJammerModel(const JammerModel& model) {
    std::cout << "[ModelManageController] updateJammerModel called for ID: " << model.id << std::endl;
    bool result = JammerModelDAO::update(model);
    if (!result) {
        std::cerr << "UpdateJammerModel failed for ID: " << model.id << std::endl;
    }
    return result;
}


bool ModelManageController::deleteJammerModel(int id) {
    std::cout << "[ModelManageController] deleteJammerModel called for ID: " << id << std::endl;
    return JammerModelDAO::deleteById(id);
}


// 按ID获取完整模型
JammerModel ModelManageController::getJammerModelById(int id) {
    std::cout << "[ModelManageController] getJammerModelById called for ID: " << id << std::endl;
    return JammerModelDAO::findById(id);
}

//改进后，获取全部的名字和ID
std::vector<std::pair<int, std::string>> ModelManageController::getAllJammerNamesAndIds() {
    return JammerModelDAO::getAllJammerNamesAndIds();
}

// 按名称搜索干扰机模型，只返回名称和ID
std::vector<std::pair<int, std::string>> ModelManageController::searchJammerModelsByName(const std::string& name) {
    return JammerModelDAO::searchJammerNamesAndIdsByName(name);
}

// ========== 探测模型方法实现 ==========
bool ModelManageController::createRadarModel(const RadarModel& model) {
    std::cout << "[ModelManageController] createRadarModel called for: " << model.name << std::endl;
    bool result = RadarModelDAO::insert(model);
    if (!result) {
        std::cerr << "CreateRadarModel failed for: " << model.name << std::endl;
    }
    return result;
}

bool ModelManageController::updateRadarModel(const RadarModel& model) {
    std::cout << "[ModelManageController] updateRadarModel called for ID: " << model.id << std::endl;
    bool result = RadarModelDAO::update(model);
    if (!result) {
        std::cerr << "UpdateRadarModel failed for ID: " << model.id << std::endl;
    }
    return result;
}

bool ModelManageController::deleteRadarModel(int id) {
    std::cout << "[ModelManageController] deleteRadarModel called for ID: " << id << std::endl;
    return RadarModelDAO::deleteById(id);
}

RadarModel ModelManageController::getRadarModelById(int id) {
    std::cout << "[ModelManageController] getRadarModelById called for ID: " << id << std::endl;
    return RadarModelDAO::findById(id);
}

std::vector<std::pair<int, std::string>> ModelManageController::getAllRadarNamesAndIds() {
    std::cout << "[ModelManageController] getAllRadarNamesAndIds called." << std::endl;
    return RadarModelDAO::getAllRadarNamesAndIds();
}

std::vector<std::pair<int, std::string>> ModelManageController::searchRadarModelsByName(const std::string& name) {
    std::cout << "[ModelManageController] searchRadarModelsByName called for name: " << name << std::endl;
    return RadarModelDAO::searchRadarNamesAndIdsByName(name);
}

// ========== 目标模型方法实现 ==========
bool ModelManageController::createTargetModel(const TargetModel& model) {
    std::cout << "[ModelManageController] createTargetModel called for: " << model.name << std::endl;
    bool result = TargetModelDAO::insert(model);
    if (!result) {
        std::cerr << "CreateTargetModel failed for: " << model.name << std::endl;
    }
    return result;
}

bool ModelManageController::updateTargetModel(const TargetModel& model) {
    std::cout << "[ModelManageController] updateTargetModel called for ID: " << model.id << std::endl;
    bool result = TargetModelDAO::update(model);
    if (!result) {
        std::cerr << "UpdateTargetModel failed for ID: " << model.id << std::endl;
    }
    return result;
}

bool ModelManageController::deleteTargetModel(int id) {
    std::cout << "[ModelManageController] deleteTargetModel called for ID: " << id << std::endl;
    return TargetModelDAO::deleteById(id);
}

TargetModel ModelManageController::getTargetModelById(int id) {
    std::cout << "[ModelManageController] getTargetModelById called for ID: " << id << std::endl;
    return TargetModelDAO::findById(id);
}

std::vector<std::pair<int, std::string>> ModelManageController::getAllTargetNamesAndIds() {
    std::cout << "[ModelManageController] getAllTargetNamesAndIds called." << std::endl;
    return TargetModelDAO::getAllTargetNamesAndIds();
}

std::vector<std::pair<int, std::string>> ModelManageController::searchTargetModelsByName(const std::string& name) {
    std::cout << "[ModelManageController] searchTargetModelsByName called for name: " << name << std::endl;
    return TargetModelDAO::findByNamePairs(name);
}

TargetModelWithRcs ModelManageController::getTargetModelWithRcsById(int id) {
    std::cout << "[ModelManageController] getTargetModelWithRcsById called for ID: " << id << std::endl;
    return TargetModelWithRcsDAO::getTargetWithRcsById(id);
}

// ========== RCS数据方法实现 ==========
bool ModelManageController::createRcsData(const RcsData& data) {
    return RcsDataDAO::insert(data);
}

bool ModelManageController::updateRcsData(const RcsData& data) {
    return RcsDataDAO::update(data);
}

bool ModelManageController::deleteRcsData(int targetId, double azimuth, double elevation) {
    return RcsDataDAO::deleteByTargetIdAndAngles(targetId, azimuth, elevation);
}

RcsData ModelManageController::getRcsData(int targetId, double azimuth, double elevation) {
    return RcsDataDAO::findByTargetIdAndAngles(targetId, azimuth, elevation);
}

std::vector<RcsData> ModelManageController::getRcsDataByTargetId(int targetId) {
    return RcsDataDAO::findByTargetId(targetId);
}

#ifndef _STATES_UPDATE_HPP_
#define _STATES_UPDATE_HPP_

#include <iostream>
#include <eigen3/Eigen/Dense>
#include "Estimator/states.hpp"

namespace Slam3D {

/**
 * @brief: 误差状态求解出来后  对原状态进行更新的 模板函数原型  
 * @details: 
 * @param _StatesType 状态的类型  
 * @param _DimError 误差状态的维度
 * @param __ErrorType 误差状态的型别  
 * @param delta_x 误差状态量 
 * @param[out] 输出的结果状态
 * @return void 
 */
template<typename _StatesType, int _DimError>
static void updateNominalStateByErrorState( 
    Eigen::Matrix<double, _DimError, 1> const& delta_x,  _StatesType &states) {}

/**
 * @brief:  模板函数的特化  
 * @details:  状态为 StatesWithImu  ， 误差状态 15  
 */
template<>
void updateNominalStateByErrorState<StatesWithImu, 15>(
        Eigen::Matrix<double, 15, 1> const& delta_x, StatesWithImu &states) {
    // std::cout<<"updateNominalStateByErrorState"<<std::endl;
    states.common_states_.P_     += delta_x.block<3, 1>(0, 0);
    states.common_states_.V_      += delta_x.block<3, 1>(3, 0);
    states.acc_bias_                           += delta_x.block<3, 1>(9, 0);
    states.gyro_bias_                         += delta_x.block<3, 1>(12, 0);
    Eigen::Vector3d axis_angle        = delta_x.block<3, 1>(6, 0);
    // 旋转更新    
    if (axis_angle.norm() > 1e-12) {
        states.common_states_.Q_ *= Eigen::Quaterniond(1, axis_angle[0] / 2, axis_angle[1] / 2, axis_angle[2] / 2);
    }                                                                                   
}

};// namespace Estimator 

#endif
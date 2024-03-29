
#pragma once 

#include <eigen3/Eigen/Dense>
#include "Estimator/state.hpp" 

namespace Slam3D {

/**
 * @brief:  状态关于其误差状态的jacobian  
 * @param {*}
 * @return {*}
 */    
template<typename _StateType, int _StateDim>
static Eigen::MatrixXd ComputerJacobianStateWithErrorState(_StateType const& state) {}

/**
 * @brief: 特化
 * @details StateWithImu 状态为 包含IMU的, 维度为 16 
 */    
template<>
Eigen::MatrixXd ComputerJacobianStateWithErrorState<StateWithImu, 16>(StateWithImu const& state) {
    Eigen::MatrixXd jacobian = Eigen::Matrix<double, 16, 15>::Zero();
    jacobian.block<6, 6>(0, 0) = Eigen::Matrix<double, 6, 6>::Identity();
    jacobian.block<6, 6>(10, 9) = Eigen::Matrix<double, 6, 6>::Identity();
    Eigen::Quaterniond q = state.Q_;
    jacobian.block<4, 3>(6, 6) << 0.5 *  -q.x(), 0.5 * -q.y(), 0.5 * -q.z(),
                                                                0.5 *  q.w(), 0.5 * -q.z(), 0.5 * q.y(),
                                                                0.5 *  q.z(), 0.5 * q.w(), 0.5 * -q.x(),
                                                                0.5 *  -q.y(), 0.5 * q.x(), 0.5 * q.w();  
    return jacobian;                                                          
}
}; // namespace Estimator


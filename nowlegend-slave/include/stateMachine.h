#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H


enum TransmissionState {
    ECHO_STANDBY = 0,
    IDENTIFICATION_STATE,
    READY_STATE,
};

struct LegendStateMachine {
    TransmissionState transmissionState {TransmissionState::ECHO_STANDBY};
    bool masterRegistered {false};
};

#endif
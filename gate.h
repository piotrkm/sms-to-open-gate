#ifndef _GATE_H_
#define _GATE_H_

#define PIN_A 4
#define PIN_B 5

#define LIMIT_SW_OPEN 6
#define LIMIT_SW_CLOSE 7

#define GATE_STATUS_OPEN          "Gate open"
#define GATE_STATUS_CLOSED        "Gate closed"
#define GATE_STATUS_IN_OPERATION  "Gate in operation"
#define GATE_STATUS_ERROR         "Gate ERROR REPORT!"
#define GATE_STATUS_UNKNOWN       "Gate status unknown!"

class gate {
  public:
    
    enum gate_status {gate_open, gate_close, gate_error, gate_in_operation};

    gate();

    String get_status();
    void set_status();
    void open_gate();
    void close_gate();

    ~gate() {};

  private:
    int status;
    long long int timestamp;



};

#endif

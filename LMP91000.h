#ifndef LMP91000_H
#define LMP91000_H

#include <stdint.h> // for various definitions
#define LMP91000_ADDRESS          0b1001000 // fixed i2c address, 0x90. Page 20

// register addresses. Page 21
#define LMP91000_STATUS           0x00
#define LMP91000_LOCK             0x01
#define LMP91000_TIACN            0x10
#define LMP91000_REFCN            0x11
#define LMP91000_MODECN           0x12

// Status register. Page 21
// bits 7:1 reserved
// bit 0
#define LMP91000_STATUS_NOT_READY 0b0 // default
#define LMP91000_STATUS_READY     0b1

// Lock register. Pages 21-22
// bits 7:1 reserved
// bit 0
#define LMP91000_LOCK_READ_MODE   0b0 // read only, default
#define LMP91000_LOCK_WRITE_MODE  0b1

// TIA control register. Page 22
// bits 7:5 reserved
// bits 4:2
#define LMP91000_TIA_GAIN_EXT     0b000 // external ref, default
#define LMP91000_TIA_GAIN1        0b001 // 2.75 kOhm
#define LMP91000_TIA_GAIN2        0b010 // 3.5  kOhm
#define LMP91000_TIA_GAIN3        0b011 // 7    kOhm
#define LMP91000_TIA_GAIN4        0b100 // 14   kOhm
#define LMP91000_TIA_GAIN5        0b101 // 35   kOhm
#define LMP91000_TIA_GAIN6        0b110 // 120  kOhm
#define LMP91000_TIA_GAIN7        0b111 // 350  kOhm
// bits 1:0
#define LMP91000_RLOAD0           0b00 // 10 Ohm
#define LMP91000_RLOAD1           0b01 // 33 Ohm
#define LMP91000_RLOAD2           0b10 // 50 Ohm
#define LMP91000_RLOAD3           0b11 // 100 Ohm, default

// Reference control register. Page 22
// bit 7, reference voltage source
#define LMP91000_REF_INT          0b0 // internal reference, default
#define LMP91000_REF_EXT          0b1 // external reference
// bits 6:5, internal zero selection
#define LMP91000_INT_Z0           0b00 // 20%
#define LMP91000_INT_Z1           0b01 // 50%, default
#define LMP91000_INT_Z2           0b10 // 67%
#define LMP91000_INT_BY           0b11 // internal zero circuitry bypassed
// bit 4, bias polarity
#define LMP91000_BIAS_NEG         0b0 // (V_WE-V_RE)<0V, default
#define LMP91000_BIAS_POS         0b1 // (V_WE-V_RE)>0V
// bits 3:0, bias selection
#define LMP91000_BIAS0            0b0000 // 0%, default
#define LMP91000_BIAS1            0b0001 // 1%
#define LMP91000_BIAS2            0b0010 // 2%
#define LMP91000_BIAS3            0b0011 // 4%
#define LMP91000_BIAS4            0b0100 // 6%
#define LMP91000_BIAS5            0b0101 // 8%
#define LMP91000_BIAS6            0b0110 // 10%
#define LMP91000_BIAS7            0b0111 // 12%
#define LMP91000_BIAS8            0b1000 // 14%
#define LMP91000_BIAS9            0b1001 // 16%
#define LMP91000_BIAS10           0b1010 // 18%
#define LMP91000_BIAS11           0b1011 // 20%
#define LMP91000_BIAS12           0b1100 // 22%
#define LMP91000_BIAS13           0b1101 // 24%

// Mode Control Register. Page 23
// bit 7, shorting FET feature
#define LMP91000_FET_DIS          0b0 // disabled, default
#define LMP91000_FET_ENA          0b1 // enabled
// bits 6:3 reserved
// bits 2:0 mode of operation
#define LMP91000_OP_MODE1         0b000 // deep sleep, default
#define LMP91000_OP_MODE2         0b001 // 2-lead ground referred galvanic cell
#define LMP91000_OP_MODE3         0b010 // Standby
#define LMP91000_OP_MODE4         0b011 // 3-lead amperometric cell
#define LMP91000_OP_MODE5         0b110 // Temperature measurement (TIA off)
#define LMP91000_OP_MODE6         0b111 // Temperature measurement (TIA on)

class LMP91000 {
  public:
    LMP91000();
    void begin();
    void begin(uint8_t cs_pin); // if done with a chip select pin

    // STATUS register pg 22
    uint8_t status();

    // LOCK register pg 21
    void lock(); // locks TIACN and REFCN registers from write
    void unlock(); // unlocks TIACN and REFCN registers
    
    // TIA Control register pg 22
    void ampGain(uint8_t gain);
    void ampResist(uint8_t res);

    // Reference Control register pg 22
    void refSource(uint8_t source);
    void internalZero(uint8_t select);
    void biasSign(uint8_t sign);
    void biasSelect(uint8_t bias);

    // Mode Control Register pg 23
    void shortFet(uint8_t fet);
    void opMode(uint8_t mode);

    uint8_t testFxn();
  //private:
    // if chip-select is implemented
    bool cs_used = false;
    uint8_t cs;

    // allow for easy register coding
    union {
      struct {
        uint8_t  STATUS:1;         /*!< bit:      0  Status of device                   */
        uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
      } bit;                       /*!< Structure used for bit  access                  */
      uint8_t reg;                 /*!< Type      used for register access              */
    } STATUS;

    union {
      struct {
        uint8_t LOCK:1;            /*!< bit:      0 Write protection                    */
        uint8_t :7;                /*!< bit:  1.. 7 Reserved                            */
      } bit;
      uint8_t reg;
    } LOCK;

    union {
      struct {
        uint8_t RLOAD:2;           /*!< bit:  0.. 1 R_Load selection                    */
        uint8_t TIA_GAIN:3;        /*!< bit:  2.. 4 TIA feedback resistance selection   */
        uint8_t :3;                /*!< bit:  5.. 7 Reserved                            */
      } bit; 
      uint8_t reg;
    } TIACN;

    union {
      struct {
        uint8_t BIAS:4;            /*!< bit:  0.. 3 BIAS selection                      */
        uint8_t BIAS_SIGN:1;       /*!< bit:      4 Selection of the bias polarity      */
        uint8_t INT_Z:2;           /*!< bit:  5.. 6 Internal zero selection             */
        uint8_t REF_SOURCE:1;      /*!< bit:      7 Reference voltage source selection  */
      } bit;
      uint8_t reg;
    } REFCN;

    union {
      struct {
        uint8_t OP_MODE:3;         /*!< bit:  0.. 2 Mode of Operation selection         */
        uint8_t :4;                /*!< bit:  3.. 6 Reserved                            */
        uint8_t FET_SHORT:1;       /*!< bit:      7 Shorting FET feature                */
      } bit;
      uint8_t reg;
    } MODECN;
    
    void i2cwrite(uint8_t reg, uint8_t value); // write value to register
    uint8_t i2cread(uint8_t reg);
};

#endif // ifndef LMP91000_H

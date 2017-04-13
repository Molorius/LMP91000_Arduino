# LMP91000_Arduino
Arduino library for the Texas Instruments LMP91000 configurable AFE potentiostat.
Datasheet: http://www.ti.com/lit/ds/symlink/lmp91000.pdf

### LMP91000 *lmp91000*
Starts the class. *lmp91000* can be replaced with the desired name. I will keep this name for the remaining commands though. 

### void *lmp91000*.begin(uint8_t pin)
Sets up the chip for usage. **pin** is optional, it is for the optional chip select. See page 24 of the datasheet. 

### uint8_t *lmp91000*.status()
Returns the status of the chip. *0* if not ready for new commands, *1* if it is ready. See datasheet page 21. 

### void *lmp91000*.lock()
Locks the registers from being written. This is the default. See datasheet page 21.

### void *lmp91000*.unlock()
Allows the registers to be written. See datasheet page 21. 

### void *lmp91000*.ampGain(uint8_t gain)
Sets the gain of the transimpedance amplifier. See datasheet page 22. Options for **gain** are:
 * **LMP91000_TIA_GAIN_EXT** - External Reference, default
 * **LMP91000_TIA_GAIN1** - 2.75 kOhm
 * **LMP91000_TIA_GAIN2** - 3.5 kOhm
 * **LMP91000_TIA_GAIN3** - 7 kOhm
 * **LMP91000_TIA_GAIN4** - 14 kOhm
 * **LMP91000_TIA_GAIN5** - 35 kOhm
 * **LMP91000_TIA_GAIN6** - 120 kOhm
 * **LMP91000_TIA_GAIN7** - 350 kOhm

### void *lmp91000*.ampResist(uint8_t res)
Sets the load resistance of the transimpedance amplifier. See datasheet page 22. Options for **res** are:
 * **LMP91000_RLOAD0** - 10 Ohm
 * **LMP91000_RLOAD1** - 33 Ohm
 * **LMP91000_RLOAD2** - 50 Ohm
 * **LMP91000_RLOAD3** - 100 Ohm, default

### void *lmp91000*.refSource(uint8_t source)
Reference voltage source selection. See datasheet page 22. Options for **source** are:
 * **LMP91000_REF_INT** - internal voltage reference, default
 * **LMP91000_REF_EXT** - external voltage reference
 
### void *lmp91000*.internalZero(uint8_t select)
Internal zero selection (percentage of the source reference). See datasheet page 22. Options are:
 * **LMP91000_INT_Z0** - 20%
 * **LMP91000_INT_Z1** - 50%, default
 * **LMP91000_INT_Z2** - 67%
 * **LMP91000_INT_BY** - Internal zero circuitry bypassed (only in O2 ground referred measurement)

### void *lmp91000*.biasSign(uint8_t sign)
Selection of the bias polarity. See datasheet page 22. Options are:
 * **0** or **LMP91000_BIAS_NEG** -  Negative (VWE – VRE)<0V, default
 * **1** or **LMP91000_BIAS_POS** - Positive (VWE-VRE)>0V
 
### void *lmp91000*.biasSelect(uint8_t bias)
Bias selection (Percentage of the source reference). See datasheet page 22. Options are:
 * **LMP91000_BIAS0** - 0%, default
 * **LMP91000_BIAS1** - 1%
 * **LMP91000_BIAS2** - 2%
 * **LMP91000_BIAS3** - 4%
 * **LMP91000_BIAS4** - 6%
 * **LMP91000_BIAS5** - 8%
 * **LMP91000_BIAS6** - 10%
 * **LMP91000_BIAS7** - 12%
 * **LMP91000_BIAS8** - 14%
 * **LMP91000_BIAS9** - 16%
 * **LMP91000_BIAS10** - 18%
 * **LMP91000_BIAS11** - 20%
 * **LMP91000_BIAS12** - 22%
 * **LMP91000_BIAS13** - 24%
 
 ### void *lmp91000*.shortFet(uint8_t fet)
 Sets or removes the shorting FET feature. See datasheet page 23. Options are:
  * **0** or **LMP91000_FET_DIS** - disabled, default
  * **1** or **LMP91000_FET_ENA** - enabled
 
 ### void *lmp91000*.opMode(uint8_t mode)
 Mode of operation selection. Datasheet page 23. Options are:
  * **LMP91000_OP_MODE0** - deep sleep, default
  * **LMP91000_OP_MODE1** - 2-lead ground referred galvanic cell
  * **LMP91000_OP_MODE2** - Standby
  * **LMP91000_OP_MODE3** - 3-lead amperometric cell
  * **LMP91000_OP_MODE4** - temperature measurement (TIA off)
  * **LMP91000_OP_MODE5** - temperature measurement (TIA on)

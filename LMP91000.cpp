#include "LMP91000.h"
#include <Wire.h>
#include <Arduino.h>

LMP91000::LMP91000() {
}

void LMP91000::begin() {
  Wire.begin();

  // save default register values to microcontroller
  STATUS.bit.STATUS     = LMP91000_STATUS_NOT_READY;
  LOCK.bit.LOCK         = LMP91000_LOCK_READ_MODE;
  TIACN.bit.TIA_GAIN    = LMP91000_TIA_GAIN_EXT;
  TIACN.bit.RLOAD       = LMP91000_RLOAD3;
  REFCN.bit.REF_SOURCE  = LMP91000_REF_INT;
  REFCN.bit.INT_Z       = LMP91000_INT_Z1;
  REFCN.bit.BIAS_SIGN   = LMP91000_BIAS_NEG;
  REFCN.bit.BIAS        = LMP91000_BIAS0;
  MODECN.bit.FET_SHORT  = LMP91000_FET_DIS;
  MODECN.bit.OP_MODE    = LMP91000_OP_MODE1;
}

void LMP91000::begin(uint8_t cs_pin) {
  cs_used = true;
  cs = cs_pin;
  pinMode(cs,OUTPUT);
  digitalWrite(cs,1);

  LMP91000::begin();
}

uint8_t LMP91000::status() {
  STATUS.reg = i2cread(LMP91000_STATUS);
  return STATUS.bit.STATUS;
}

void LMP91000::lock() {
  LOCK.bit.LOCK = LMP91000_LOCK_READ_MODE;
  i2cwrite(LMP91000_LOCK, LOCK.reg);
}

void LMP91000::unlock() {
  LOCK.bit.LOCK = LMP91000_LOCK_WRITE_MODE;
  i2cwrite(LMP91000_LOCK, LOCK.reg);
}

void LMP91000::ampGain(uint8_t gain) {
  TIACN.bit.TIA_GAIN = gain;
  i2cwrite(LMP91000_TIACN, TIACN.reg);
}

void LMP91000::ampResist(uint8_t res) {
  TIACN.bit.RLOAD = res;
  i2cwrite(LMP91000_TIACN, TIACN.reg);
}

void LMP91000::refSource(uint8_t source) {
  REFCN.bit.REF_SOURCE = source;
  i2cwrite(LMP91000_REFCN, REFCN.reg);
}

void LMP91000::internalZero(uint8_t select) {
  REFCN.bit.INT_Z = select;
  i2cwrite(LMP91000_REFCN, REFCN.reg);
}

void LMP91000::biasSign(uint8_t sign) {
  REFCN.bit.BIAS_SIGN = sign;
  i2cwrite(LMP91000_REFCN, REFCN.reg);
}

void LMP91000::biasSelect(uint8_t bias) {
  REFCN.bit.BIAS = bias;
  i2cwrite(LMP91000_REFCN, REFCN.reg);
}

void LMP91000::shortFet(uint8_t fet) {
  MODECN.bit.FET_SHORT = fet;
  i2cwrite(LMP91000_MODECN, MODECN.reg);
}

void LMP91000::opMode(uint8_t mode) {
  MODECN.bit.OP_MODE = mode;
  i2cwrite(LMP91000_MODECN, MODECN.reg);
}

void LMP91000::i2cwrite(uint8_t reg,uint8_t value) {
  if(cs_used) digitalWrite(cs,0);
  
  Wire.beginTransmission(LMP91000_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();

  if(cs_used) digitalWrite(cs,1);
}

uint8_t LMP91000::i2cread(uint8_t reg) {
  if(cs_used) digitalWrite(cs,0);
  
  uint8_t val = 0;
  Wire.beginTransmission(LMP91000_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false); // necessary?
  Wire.requestFrom(LMP91000_ADDRESS,1);
  if(Wire.available()) {
    val = Wire.read();
  }

  if(cs_used) digitalWrite(cs,1);
  return val;
}


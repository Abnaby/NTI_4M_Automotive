/*
 * Function Description:  The Function takes an ADC value and calculates the corresponding voltage based on the reference voltage VREF
 *
 * Input Parameter:  copy_u16ADC_VAL  ADC Value 
 					 copu_u8Vref      Vref
 * Output Parameter: float value for corresponding voltage
 */

f32 getVoltageFromADC(u16 copy_u16ADC_VAL , u8 copu_u8Vref)
{
	f32 Loc_f32Voltage = 0 ; 
	Loc_f32Voltage = (copy_u16ADC_VAL * copu_u8Vref) / (1024.0) ; // 10-bit ADC (2^10 = 1024)
	return Loc_f32Voltage ; 
}
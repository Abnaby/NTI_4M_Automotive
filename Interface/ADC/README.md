# Interfacing - ADC

## getVoltageFromADC Function

The `getVoltageFromADC()` function is a C function that calculates the voltage corresponding to a given ADC value based on the reference voltage VREF for 10-Bit ADC.

## Usage

To use the `getVoltageFromADC() `function in your C program, you can follow these steps:

1. Copy the function code into your C source file.
2. Call the function with the desired ADC value and reference voltage as arguments.
3. Store the returned voltage value in a variable for further processing or output.

Here's an example usage of the `getVoltageFromADC()` function:

```C
// Function declaration    
f32 getVoltageFromADC(u16 copy_u16ADC_VAL , u8 copu_u8Vref);

int main()
{
    u16 adcValue = 512; // Example ADC value
    f32 VREF = 5.0;          // Example reference voltage

    f32 voltage = getVoltageFromADC(adcValue, VREF);
    printf("ADC value: %d\n", adcValue);
    printf("Reference voltage: %0.2f V\n", VREF);
    printf("Voltage: %0.2f V\n", voltage);

    return 0;
}

```

Result 

 ![Result]( ./Result/Result.JPG) 

 ## *Contributing*  
Bug reports, feature requests, and so on are always welcome. Feel free to leave a note in the Issues section.
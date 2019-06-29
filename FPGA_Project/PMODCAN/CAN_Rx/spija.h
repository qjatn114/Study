/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Digilent

  @File Name
    spija.h

  @Description
        This file groups the declarations of the functions that implement
        the SPIFLASH library (defined in spija.c).
        Include the file in the project when this library is needed.
        Use #include "spija.h" in the source files where the functions are needed.


    https://github.com/Digilent/Basys-MX3-library/tree/master/LibPack/LibPack.X  

 */
/* ************************************************************************** */

#ifndef _SPIJA_H    /* Guard against multiple inclusion */
    #define _SPI_SS_PIN     10    // RC2    
    #define _SPI_MOSI_PIN   11    // RC1
    #define _SPI_MISO_PIN   12    // RC4
    #define _SPI_SCK_PIN    22    // RG6
#endif /* _SPIJA_H */

//#ifdef __cplusplus
//extern "C" {
//#endif

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    void SPIJA_Init(void);
    void SPIJA_ConfigureSPI(unsigned int spiFreq, unsigned char pol, unsigned char edge);
    unsigned char SPIJA_RawTransferByte(unsigned char bVal);
    void SPIJA_TransferBytes(int bytesNumber, unsigned char *pbRdData, unsigned char *pbWrData);
    void SPIJA_Close();

//private functions
    void SPIJA_ConfigurePins();

    /* Provide C++ Compatibility */
//#ifdef __cplusplus
//}
//#endif

/* *****************************************************************************
 End of File
 */

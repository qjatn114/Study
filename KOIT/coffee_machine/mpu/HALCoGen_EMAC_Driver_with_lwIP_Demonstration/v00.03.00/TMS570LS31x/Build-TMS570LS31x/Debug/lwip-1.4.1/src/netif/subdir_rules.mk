################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
lwip-1.4.1/src/netif/ethernetif.obj: C:/ti/Hercules/HALCoGen\ EMAC\ Driver\ with\ lwIP\ Demonstration/v00.02.00/lwip-1.4.1/src/netif/ethernetif.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -g --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/TMS570LS31x/HALCoGen-TMS570LS31x/include" --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/example/hdk/inc" --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/lwip-1.4.1/ports/hdk/check" --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/lwip-1.4.1/ports/hdk" --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/lwip-1.4.1" --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/lwip-1.4.1/src/include" --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/lwip-1.4.1/apps/httpserver_raw" --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/lwip-1.4.1/src/include/ipv4" --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/lwip-1.4.1/ports/hdk/include/netif" --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/lwip-1.4.1/ports/hdk/netif" --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/lwip-1.4.1/ports/hdk/include" --include_path="C:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.02.00/lwip-1.4.1/ports/hdk/netif" --diag_warning=225 --display_error_number --diag_wrap=off --enum_type=packed --preproc_with_compile --preproc_dependency="lwip-1.4.1/src/netif/ethernetif.pp" --obj_directory="lwip-1.4.1/src/netif" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '



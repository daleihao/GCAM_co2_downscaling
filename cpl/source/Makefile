#------------------------------------------------------------------------
# Makefile for objects/ccsmcpl
# tcraig 19-Apr-2010
#------------------------------------------------------------------------

#PATHOFFSET = path to objects directory
PATHOFFSET = ../../cvs/objects
include ${PATHOFFSET}/build/linux/configure.gcam

OBJS       =  GCAM_E3SM_interface.o GCAM_E3SM_interface_wrapper.o get_data_helper.o remap_data.o set_data_helper.o carbon_scalers.o aspatial_data.o emiss_downscale.o

cpl_dir:   ${OBJS}

-include $(DEPS)


clean:
	rm *.o *.mod

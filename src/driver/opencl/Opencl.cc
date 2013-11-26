/*
 *  Multi2Sim
 *  Copyright (C) 2012  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Opencl.h"

namespace SIDriver
{

int OpenclDriver::OpenclABIInitImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIMemAllocImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIMemReadImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIMemWriteImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIMemCopyImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIMemFreeImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIProgramCreateImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIProgramSetBinaryImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIKernalCreateImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIKernelSetArgValueImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIKernelSetArgPointerImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIKernelSetArgImageImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABIKernelSetArgSamplerImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABINDRangeCreateImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABINDRangeGetBufferEntriesImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABINDRangeSendWorkGoupsImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABINDRangeFinishImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABINDRangePassMemObjsImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABINDRangeSetFusedImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABINDRangeFlushImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABINDRangeFreeImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABINDRangeStartImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

int OpenclDriver::OpenclABINDRangeEndImpl(/*FIXME: X86Context *ctx*/)
{
	// Return
	return 0;
}

#if 0
/*
 * Class 'OpenclDriver'
 */

void OpenclDriverCreate(OpenclDriver *self, X86Emu *x86_emu, SIEmu *si_emu)
{
	/* Parent */
	DriverCreate(asDriver(self), x86_emu);

	/* Initialize */
	self->si_emu = si_emu;

	/* Assign driver to host emulator */
	x86_emu->opencl_driver = self;
	si_emu->opencl_driver = self;

	/* List of Southern Islands programs */
	self->si_program_list = list_create();
	list_add(self->si_program_list, NULL);

	/* List of SI kernels */
	self->si_kernel_list = list_create();
	list_add(self->si_kernel_list, NULL);

	/* List of SI nd-ranges */
	self->si_ndrange_list = list_create();
}


void OpenclDriverDestroy(OpenclDriver *self)
{
	struct opencl_si_program_t *program;
	struct opencl_si_kernel_t *kernel;

	int index;

	/* Free list of Southern Islands programs */
	LIST_FOR_EACH(self->si_program_list, index)
		if ((program = list_get(self->si_program_list, index)))
			opencl_si_program_free(program);
	list_free(self->si_program_list);

	/* Free list of Southern Islands kernels */
	LIST_FOR_EACH(self->si_kernel_list, index)
		if ((kernel = list_get(self->si_kernel_list, index)))
			opencl_si_kernel_free(kernel);
	list_free(self->si_kernel_list);

	/* Free list of Southern Islands nd-ranges*/
	assert(!list_count(self->si_ndrange_list));
	list_free(self->si_ndrange_list);
}


/* This function is called when all work groups from an ND-Range have
 * been scheduled (i.e., ndrange->waiting_work_groups is empty) */
void OpenclDriverRequestWork(OpenclDriver *self, SINDRange *ndrange)
{
	X86Emu *emu = asDriver(self)->emu;

	opencl_debug("%s: nd-range %d waiting queue is empty\n", 
		__FUNCTION__, ndrange->id);

	X86EmuProcessEventsSchedule(emu);
}


/* This function is called when all work groups from an ND-Range have
 * been scheduled and completed (i.e., ndrange->waiting_work_groups and 
 * ndrange->running_work_groups are both empty) */
void OpenclDriverNDRangeComplete(OpenclDriver *self, SINDRange *ndrange)
{
	X86Emu *emu = asDriver(self)->emu;

	opencl_debug("%s: nd-range %d complete\n", 
		__FUNCTION__, ndrange->id);

	X86EmuProcessEventsSchedule(emu);
}



/*
 * Public
 */

#define SI_DRIVER_MAX_WORK_GROUP_BUFFER_SIZE (1024*1024)


static char *opencl_err_abi_call =
	"\tAn invalid function code was generated by the your application as\n"
	"\tan argument of a system call reserved for the Multi2Sim OpenCL\n"
	"\tRuntime library. Please recompile your application and try again.\n";

/* List of OpenCL Runtime calls */
enum opencl_abi_call_t
{
	opencl_abi_invalid = 0,
#define OPENCL_ABI_CALL(name, code) opencl_abi_##name = code,
#include "opencl.dat"
#undef OPENCL_ABI_CALL
	opencl_abi_call_count
};


/* List of OpenCL ABI call names */
char *opencl_abi_call_name[opencl_abi_call_count + 1] =
{
	NULL,
#define OPENCL_ABI_CALL(name, code) #name,
#include "opencl.dat"
#undef OPENCL_ABI_CALL
	NULL
};

/* Forward declarations of OpenCL Runtime functions */
#define OPENCL_ABI_CALL(name, code) \
	static int opencl_abi_##name##_impl(X86Context *ctx);
#include "opencl.dat"
#undef OPENCL_ABI_CALL


/* List of OpenCL Runtime functions */
typedef int (*opencl_abi_call_t)(X86Context *ctx);
static opencl_abi_call_t opencl_abi_call_table[opencl_abi_call_count + 1] =
{
	NULL,
#define OPENCL_ABI_CALL(name, code) opencl_abi_##name##_impl,
#include "opencl.dat"
#undef OPENCL_ABI_CALL
	NULL
};


/* Debug */
int opencl_debug_category;



int OpenclDriverCall(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;

	/* Variables */
	int code;
	int ret;

	/* Function code */
	code = regs->ebx;
	if (code <= opencl_abi_invalid || code >= opencl_abi_call_count)
		fatal("%s: invalid OpenCL ABI call (code %d).\n%s",
			__FUNCTION__, code, opencl_err_abi_call);

	/* Debug */
	x86_sys_debug("  %s (code %d)\n", opencl_abi_call_name[code], code);
	opencl_debug("OpenCL ABI call '%s' (code %d)\n",
		opencl_abi_call_name[code], code);

	/* Call OpenCL Runtime function */
	assert(opencl_abi_call_table[code]);
	ret = opencl_abi_call_table[code](ctx);

	/* Return value */
	return ret;
}




/*
 * OpenCL ABI call #1 - init
 *
 * Returns the version of the OpenCL driver.
 *
 * @param struct opencl_version_t *version
 *
 * 	The driver returns its version information in this argument, with a
 * 	data structure formed of two integer fields:
 *
 * 	struct opencl_version_t
 * 	{
 * 		int major;
 * 		int minor;
 * 	};
 *
 * @return
 *	The function always returns 0.
 */

/* NOTE: when modifying the values of these two macros, the same values should
 * be reflected in 'runtime/opencl/platform.c'. */
#define OPENCL_VERSION_MAJOR  5
#define OPENCL_VERSION_MINOR  2173

struct opencl_version_t
{
	int major;
	int minor;
};

static int opencl_abi_init_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	unsigned int version_ptr;
	struct opencl_version_t version;

	/* Arguments */
	version_ptr = regs->ecx;
	opencl_debug("\tversion_ptr=0x%x\n", version_ptr);

	/* Return version */
	assert(sizeof(struct opencl_version_t) == 8);
	version.major = OPENCL_VERSION_MAJOR;
	version.minor = OPENCL_VERSION_MINOR;
	mem_write(mem, version_ptr, sizeof version, &version);
	opencl_debug("\tMulti2Sim OpenCL implementation in host: v. %d.%d.\n",
		OPENCL_VERSION_MAJOR, OPENCL_VERSION_MINOR);
	opencl_debug("\tMulti2Sim OpenCL Runtime in guest: v. %d.%d.\n",
		version.major, version.minor);

	/* Return success */
	return 0;
}




/*
 * OpenCL ABI call #2 - si_mem_alloc
 *
 * Allocates memory in the Southern Islands device.
 *
 * @param unsigned int size
 *
 * 	Number of bytes to allocate.
 *
 * @return void *
 *
 *	The function returns a pointer in the device memory space. This pointer
 *	should not be dereferenced in the runtime, but instead passed to other
 *	ABI calls taking device pointers as input arguments.
 */

static int opencl_abi_si_mem_alloc_impl(X86Context *ctx)
{
	X86Emu *x86_emu = ctx->emu;
	OpenclDriver *driver = x86_emu->opencl_driver;
	SIEmu *si_emu = driver->si_emu;
	SIGpu *si_gpu = driver->si_gpu;

	struct x86_regs_t *regs = ctx->regs;

	unsigned int device_ptr;
	unsigned int size;

	/* Arguments */
	size = regs->ecx;
	opencl_debug("\tsize = %u\n", size);

	if (driver->fused)
	{
		fatal("%s: GPU is set as a fused device, so the x86 "
			"allocator should be used", __FUNCTION__);
	}

	if (si_gpu)
	{
		/* Allocate starting from nearest page boundary */
		if (si_emu->video_mem_top & si_gpu->mmu->page_mask)
		{
			si_emu->video_mem_top += si_gpu->mmu->page_size -
				(si_emu->video_mem_top & 
				 si_gpu->mmu->page_mask);
		}
	}

	/* Map new pages */
	mem_map(si_emu->video_mem, si_emu->video_mem_top, size,
		mem_access_read | mem_access_write);

	/* Virtual address of memory object */
	device_ptr = si_emu->video_mem_top;
	opencl_debug("\t%d bytes of device memory allocated at 0x%x\n",
		size, device_ptr);

	/* For now, memory allocation in device memory is done by just 
	 * incrementing a pointer to the top of the global memory space. 
	 * Since memory deallocation is not implemented, "holes" in the 
	 * memory space are not considered. */
	si_emu->video_mem_top += size;

	/* Return device pointer */
	return device_ptr;
}




/*
 * OpenCL ABI call #3 - si_mem_read
 *
 * Read memory from Southern Islands device into host memory space.
 *
 * @param void *host_ptr
 *
 * 	Destination pointer in host memory space.
 *
 * @param void *device_ptr
 *
 * 	Source pointer in device memory space.
 *
 * @param unsigned int size
 *
 * 	Number of bytes to read.
 *
 * @return void
 *
 *	The function does not have any return value.
 */

static int opencl_abi_si_mem_read_impl(X86Context *ctx)
{
	X86Emu *x86_emu = ctx->emu;
	OpenclDriver *driver = x86_emu->opencl_driver;
	SIEmu *si_emu = driver->si_emu;

	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	unsigned int host_ptr;
	unsigned int device_ptr;
	unsigned int size;

	void *buf;

	if (driver->fused)
	{
		fatal("%s: GPU is set as a fused device, so the x86 "
			"memory operations should be used", __FUNCTION__);
	}

	/* Arguments */
	host_ptr = regs->ecx;
	device_ptr = regs->edx;
	size = regs->esi;
	opencl_debug("\thost_ptr = 0x%x, device_ptr = 0x%x, size = %d bytes\n",
			host_ptr, device_ptr, size);

	/* Check memory range */
	if (device_ptr + size > si_emu->video_mem_top)
		fatal("%s: accessing device memory not allocated",
				__FUNCTION__);

	/* Read memory from device to host */
	buf = xmalloc(size);
	mem_read(si_emu->video_mem, device_ptr, size, buf);
	mem_write(mem, host_ptr, size, buf);
	free(buf);

	/* Return */
	return 0;
}




/*
 * OpenCL ABI call #4 - si_mem_write
 *
 * Write memory from host into Southern Islands device.
 *
 * @param void *device_ptr
 *
 * 	Destination pointer in device memory.
 *
 * @param void *host_ptr
 *
 * 	Source pointer in host memory.
 *
 * @param unsigned int size
 *
 * 	Number of bytes to read.
 *
 * @return void
 *
 *	The function does not have any return value.
 */

static int opencl_abi_si_mem_write_impl(X86Context *ctx)
{
	X86Emu *x86_emu = ctx->emu;
	OpenclDriver *driver = x86_emu->opencl_driver;
	SIEmu *si_emu = driver->si_emu;

	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *x86_mem = ctx->mem;

	unsigned int device_ptr;
	unsigned int host_ptr;
	unsigned int size;

	void *buf;

	if (driver->fused)
	{
		fatal("%s: GPU is set as a fused device, so the x86 "
			"memory operations should be used", __FUNCTION__);
	}

	/* Arguments */
	device_ptr = regs->ecx;
	host_ptr = regs->edx;
	size = regs->esi;
	opencl_debug("\tdevice_ptr = 0x%x, host_ptr = 0x%x, size = %d bytes\n",
			device_ptr, host_ptr, size);

	/* Check memory range */
	if (device_ptr + size > si_emu->video_mem_top)
		fatal("%s: accessing device memory not allocated",
				__FUNCTION__);

	/* Write memory from host to device */
	buf = xmalloc(size);
	mem_read(x86_mem, host_ptr, size, buf);
	mem_write(si_emu->video_mem, device_ptr, size, buf);
	free(buf);

	/* Return */
	return 0;
}




/*
 * OpenCL ABI call #5 - si_mem_copy
 *
 * Copy memory across two different regions of the Southern Islands device
 * memory space.
 *
 * @param void *dest_ptr
 *
 * 	Destination pointer in device memory.
 *
 * @param void *src_ptr
 *
 * 	Source pointer in device memory.
 *
 * @param unsigned int size
 *
 * 	Number of bytes to read.
 *
 * @return void
 *
 *	The function does not have any return value.
 */

static int opencl_abi_si_mem_copy_impl(X86Context *ctx)
{
	X86Emu *x86_emu = ctx->emu;
	OpenclDriver *driver = x86_emu->opencl_driver;
	SIEmu *si_emu = driver->si_emu;

	struct x86_regs_t *regs = ctx->regs;

	unsigned int dest_ptr;
	unsigned int src_ptr;
	unsigned int size;

	void *buf;

	if (driver->fused)
	{
		fatal("%s: GPU is set as a fused device, so the x86 "
			"memory operations should be used", __FUNCTION__);
	}

	/* Arguments */
	dest_ptr = regs->ecx;
	src_ptr = regs->edx;
	size = regs->esi;
	opencl_debug("\tdest_ptr = 0x%x, src_ptr = 0x%x, size = %d bytes\n",
			dest_ptr, src_ptr, size);

	/* Check memory range */
	if (src_ptr + size > si_emu->video_mem_top ||
			dest_ptr + size > si_emu->video_mem_top)
		fatal("%s: accessing device memory not allocated",
				__FUNCTION__);

	/* Write memory from host to device */
	buf = xmalloc(size);
	mem_read(si_emu->video_mem, src_ptr, size, buf);
	mem_write(si_emu->video_mem, dest_ptr, size, buf);
	free(buf);

	/* Return */
	return 0;
}


/*
 * OpenCL ABI call #6 - si_mem_free
 *
 * Deallocated memory in Southern Islands global memory scope.
 *
 * @param unsigned int device_ptr
 *
 * 	Memory address in device global memory returned previously by a call to
 *	'si_mem_alloc'.
 *
 * @return void
 *
 *	No value is returned.
 */

static int opencl_abi_si_mem_free_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;

	unsigned int device_ptr;

	/* Arguments */
	device_ptr = regs->ecx;
	opencl_debug("\tdevice_ptr = %u\n", device_ptr);

	/* For now, this call is ignored. No deallocation of global memory can
	 * happen. */

	/* Return device pointer */
	return device_ptr;
}



/*
 * OpenCL ABI call #7 - si_program_create
 *
 * Create a Southern Islands program object and return a unique identifier
 * for it.
 *
 * @return int
 *
 *	Unique program ID.
 */

static int opencl_abi_si_program_create_impl(X86Context *ctx)
{
	X86Emu *emu = ctx->emu;
	OpenclDriver *driver = emu->opencl_driver;

	struct opencl_si_program_t *program;

	/* Create program and add it to list of SI programs */
	program = opencl_si_program_create(driver, driver->si_program_list->count);
	list_add(driver->si_program_list, program);
	opencl_debug("\tnew program ID = %d\n", program->id);

	/* Return program ID */
	return program->id;
}




/*
 * OpenCL ABI call #8 - si_program_set_binary
 *
 * Associate a binary to a Southern Islands program.
 *
 * @param int program_id
 *
 * 	Program ID, as returned by a previous ABI call to 'si_program_create'.
 *
 * @param void *buf
 *
 * 	Pointer to the memory space where the program binary can be found.
 *
 * @param unsigned int size
 *
 * 	Size of the program binary
 *
 * @return void
 *
 *	No return value.
 */

static int opencl_abi_si_program_set_binary_impl(X86Context *ctx)
{
	X86Emu *emu = ctx->emu;
	OpenclDriver *driver = emu->opencl_driver;

	struct x86_regs_t *regs = ctx->regs;
	struct opencl_si_program_t *program;

	int program_id;
	unsigned int bin_ptr;
	unsigned int bin_size;

	void *buf;

	/* Arguments */
	program_id = regs->ecx;
	bin_ptr = regs->edx;
	bin_size = regs->esi;
	opencl_debug("\tprogram_id=%d, bin_ptr=0x%x, size=%u\n",
			program_id, bin_ptr, bin_size);

	/* Get program */
	program = list_get(driver->si_program_list, program_id);
	if (!program)
		fatal("%s: invalid program ID (%d)",
				__FUNCTION__, program_id);

	/* Set the binary */
	buf = xmalloc(bin_size);
	mem_read(ctx->mem, bin_ptr, bin_size, buf);
	opencl_si_program_set_binary(program, buf, bin_size);
	free(buf);

	/* No return value */
	return 0;
}



/*
 * OpenCL ABI call #9 - si_kernel_create
 *
 * Create a Southern Islands kernel object and return a unique identifier
 * for it.
 *
 * @param int program_id
 *
 * 	Program ID, as returned by ABI call 'si_program_create'
 *
 * @param char *func_name
 *
 * 	Kernel function name in the program.
 *
 * @return int
 *
 *	Unique kernel ID.
 */

static int opencl_abi_si_kernel_create_impl(X86Context *ctx)
{
	X86Emu *emu = ctx->emu;
	OpenclDriver *driver = emu->opencl_driver;

	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	struct opencl_si_kernel_t *kernel;
	struct opencl_si_program_t *program;

	unsigned int func_name_ptr;

	int program_id;
	int size;

	char func_name[MAX_STRING_SIZE];

	/* Arguments */
	program_id = regs->ecx;
	func_name_ptr = regs->edx;
	opencl_debug("\tprogram_id=%d, func_name_ptr=0x%x\n",
			program_id, func_name_ptr);

	/* Read function name */
	size = mem_read_string(mem, func_name_ptr, sizeof func_name, func_name);
	if (size == sizeof func_name)
		fatal("%s: buffer too small", __FUNCTION__);
	opencl_debug("\tfunc_name='%s'\n", func_name);

	/* Get program object */
	program = list_get(driver->si_program_list, program_id);
	if (!program)
		fatal("%s: invalid program ID (%d)",
				__FUNCTION__, program_id);

	/* Create kernel */
	kernel = opencl_si_kernel_create(driver->si_kernel_list->count,
			program, func_name);
	list_add(driver->si_kernel_list, kernel);
	opencl_debug("\tnew kernel ID = %d\n", kernel->id);

	/* Return kernel ID */
	return kernel->id;
}




/*
 * OpenCL ABI call #10 - si_kernel_set_arg_value
 *
 * Set a kernel argument with a basic type (cl_char, cl_int, cl_float, ...).
 *
 * @param int kernel_id
 *
 * 	Kernel ID, as returned by ABI call 'si_kernel_create'
 *
 * @param int index
 *
 * 	Argument index to set.
 *
 * @param void *host_ptr
 *
 *	Address in host memory containing the value of the argument. The memory
 * 	pointed to by this variable will be copied internally, keeping a copy of
 * 	the argument for future use.
 *
 * @param unsigned int size
 *
 * 	Argument size. This size must match the size encoded in the kernel
 * 	metadata for this particular argument.
 *
 * @return int
 *
 *	Unique kernel ID.
 */

static int opencl_abi_si_kernel_set_arg_value_impl(X86Context *ctx)
{
	X86Emu *emu = ctx->emu;
	OpenclDriver *driver = emu->opencl_driver;

	struct x86_regs_t *regs = ctx->regs;
	struct opencl_si_kernel_t *kernel;
	SIArg *arg;

	int kernel_id;

	unsigned int index;
	unsigned int host_ptr;
	unsigned int size;

	/* Arguments */
	kernel_id = regs->ecx;
	index = regs->edx;
	host_ptr = regs->esi;
	size = regs->edi;
	opencl_debug("\tkernel_id=%d, index=%d\n", kernel_id, index);
	opencl_debug("\thost_ptr=0x%x, size=%u\n", host_ptr, size);

	/* Get kernel */
	kernel = list_get(driver->si_kernel_list, kernel_id);
	if (!kernel)
		fatal("%s: invalid kernel ID (%d)",
				__FUNCTION__, kernel_id);

	/* Get argument */
	arg = asSIArg(ListGoto(kernel->arg_list, index));
	if (!arg || arg->type != SIArgTypeValue)
		fatal("%s: invalid argument %d type",
				__FUNCTION__, index);

	/* Check valid size */
	if (size != arg->size)
		fatal("%s: argument %d: size %d expected, %d found",
				__FUNCTION__, index, arg->size, size);

	/* Free a possible previous value */
	if (arg->value.value_ptr)
		free(arg->value.value_ptr);

	/* Save value */
	arg->set = 1;
	arg->value.value_ptr = xmalloc(size);
	mem_read(ctx->mem, host_ptr, size, arg->value.value_ptr);

	/* No return value */
	return 0;
}




/*
 * OpenCL ABI call #11 - si_kernel_set_arg_pointer
 *
 * Set a kernel argument of type 'cl_mem', or local memory. In general, any
 * argument that uses the 'pointer' name as first token in the metadata entry of
 * the kernel binary.
 *
 * @param int kernel_id
 *
 * 	Kernel ID, as returned by ABI call 'si_kernel_create'
 *
 * @param int index
 *
 * 	Argument index to set.
 *
 * @param void *device_ptr
 *
 *	If the argument represents a 'cl_mem' object in global memory, pointer
 *	to device memory containing the data, as returned by a previous call to
 *	'si_mem_alloc'.
 *	If the argument is a variable in local memory, the purpose of the call
 *	is just allocating space for it, so this value should be NULL.
 *
 * @param unsigned int size
 *
 *	If the argument represents a 'cl_mem' object, size allocated in global
 *	memory for the object.
 *	If the argument is a variable in local memory, number of bytes to be
 *	allocated in the device local memory.
 *
 * @return int
 *
 *	Unique kernel ID.
 */

static int opencl_abi_si_kernel_set_arg_pointer_impl(X86Context *ctx)
{
	X86Emu *emu = ctx->emu;
	OpenclDriver *driver = emu->opencl_driver;

	struct x86_regs_t *regs = ctx->regs;
	struct opencl_si_kernel_t *kernel;
	SIArg *arg;

	int kernel_id;

	unsigned int index;
	unsigned int device_ptr;
	unsigned int size;

	/* Arguments */
	kernel_id = regs->ecx;
	index = regs->edx;
	device_ptr = regs->esi;
	size = regs->edi;
	opencl_debug("\tkernel_id=%d, index=%d\n", kernel_id, index);
	opencl_debug("\tdevice_ptr=0x%x, size=%u\n", device_ptr, size);

	/* Get kernel */
	kernel = list_get(driver->si_kernel_list, kernel_id);
	if (!kernel)
		fatal("%s: invalid kernel ID (%d)",
				__FUNCTION__, kernel_id);

	/* Get argument */
	arg = asSIArg(ListGoto(kernel->arg_list, index));
	if (!arg || arg->type != SIArgTypePointer)
		fatal("%s: invalid argument %d type",
				__FUNCTION__, index);

	/* Record size and value */
	arg->set = 1;
	arg->size = size;
	arg->pointer.device_ptr = device_ptr;

	/* No return value */
	return 0;
}




/*
 * OpenCL ABI call #12 - si_kernel_set_arg_image
 *
 * Set a kernel argument of type 'cl_image'.
 *
 * @param int kernel_id
 *
 * 	Kernel ID, as returned by ABI call 'si_kernel_create'
 *
 * @param int index
 *
 * 	Argument index to set.
 *
 * @param [...] FIXME - not decided yet
 *
 * @return int
 *
 *	Unique kernel ID.
 */

static int opencl_abi_si_kernel_set_arg_image_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;

	int kernel_id;
	unsigned int index;

	/* Arguments */
	kernel_id = regs->ecx;
	index = regs->edx;
	opencl_debug("\tkernel_id=%d, index=%d\n", kernel_id, index);

	/* Not yet */
	fatal("%s: not implemented", __FUNCTION__);

	/* No return value */
	return 0;
}




/*
 * OpenCL ABI call #13 - si_kernel_set_arg_sampler
 *
 * Set a kernel argument of type 'cl_sampler'.
 *
 * @param int kernel_id
 *
 * 	Kernel ID, as returned by ABI call 'si_kernel_create'
 *
 * @param int index
 *
 * 	Argument index to set.
 *
 * @param [...] FIXME - not decided yet
 *
 * @return int
 *
 *	Unique kernel ID.
 */

static int opencl_abi_si_kernel_set_arg_sampler_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;

	int kernel_id;
	unsigned int index;

	/* Arguments */
	kernel_id = regs->ecx;
	index = regs->edx;
	opencl_debug("\tkernel_id=%d, index=%d\n", kernel_id, index);

	/* Not yet */
	fatal("%s: not implemented", __FUNCTION__);

	/* No return value */
	return 0;
}




/*
 * OpenCL ABI call #14 - si_ndrange_create
 *
 * Create and initialize an ND-Range for the supplied kernel.
 *
 * @param int kernel_id
 *
 * 	Kernel ID, as returned by ABI call 'si_kernel_create'
 *
 * @param int work_dim
 *
 * 	Number of work dimensions. This is an integer number between 1 and 3,
 * 	which determines the number of elements of the following arrays.
 *
 * @param unsigned int *global_offset
 *
 *	Array of 'work_dim' integers containing global offsets.
 *
 * @param unsigned int *global_size
 *
 *	Array of 'work_dim' integers containing the ND-Range global size in each
 *	dimension.
 *
 * @param unsigned int *local_size
 *
 *	Array of 'work_dim' integers containing the local size in each
 *	dimension.
 *
 * @return int
 *
 *	ID of new nd-range
 */

static int opencl_abi_si_ndrange_create_impl(X86Context *ctx)
{
	SIArg *arg, *arg_copy;
	X86Emu *x86_emu = ctx->emu;
	OpenclDriver *driver = x86_emu->opencl_driver;
	SIEmu *si_emu = driver->si_emu;
	SIGpu *si_gpu = driver->si_gpu;

	SINDRange *ndrange;

	struct mem_t *mem = ctx->mem;
	struct opencl_si_kernel_t *kernel;
	struct SIBinaryUserElement *user_elements;
	struct x86_regs_t *regs = ctx->regs;

	int i;
	int kernel_id;
	int user_element_count;
	int work_dim;

	unsigned int global_offset_ptr;
	unsigned int global_size_ptr;
	unsigned int local_size_ptr;

	unsigned int global_offset[3];
	unsigned int global_size[3];
	unsigned int local_size[3];

	if (driver->fused)
		si_emu->global_mem = ctx->mem;

	/* Arguments */
	kernel_id = regs->ecx;
	work_dim = regs->edx;
	global_offset_ptr = regs->esi;
	global_size_ptr = regs->edi;
	local_size_ptr = regs->ebp;
	opencl_debug("\tkernel_id=%d, work_dim=%d\n", kernel_id, work_dim);
	opencl_debug("\tglobal_offset_ptr=0x%x, global_size_ptr=0x%x, "
		"local_size_ptr=0x%x\n", global_offset_ptr, global_size_ptr, 
		local_size_ptr);
	
	/* Debug */
	assert(IN_RANGE(work_dim, 1, 3));
	mem_read(mem, global_offset_ptr, work_dim * 4, global_offset);
	mem_read(mem, global_size_ptr, work_dim * 4, global_size);
	mem_read(mem, local_size_ptr, work_dim * 4, local_size);
	for (i = 0; i < work_dim; i++)
		opencl_debug("\tglobal_offset[%d] = %u\n", i, global_offset[i]);
	for (i = 0; i < work_dim; i++)
		opencl_debug("\tglobal_size[%d] = %u\n", i, global_size[i]);
	for (i = 0; i < work_dim; i++)
		opencl_debug("\tlocal_size[%d] = %u\n", i, local_size[i]);

	/* Get kernel */
	kernel = list_get(driver->si_kernel_list, kernel_id);
	if (!kernel)
		fatal("%s: invalid kernel ID (%d)", __FUNCTION__, kernel_id);

	/* Create ND-Range */
	ndrange = new(SINDRange, si_emu);
	opencl_debug("\tcreated ndrange %d\n", ndrange->id);

	ndrange->local_mem_top = kernel->mem_size_local;
	struct SIBinaryDictEntry *si_dict_entry =
			SIBinaryGetSIDictEntry(kernel->bin_file);
	ndrange->num_sgpr_used = SIBinaryDictEntryGetNumSgpr(si_dict_entry);
	ndrange->num_vgpr_used = SIBinaryDictEntryGetNumVgpr(si_dict_entry);
	ndrange->wg_id_sgpr = SIBinaryDictEntryGetComputePgmRsrc2(si_dict_entry)->user_sgpr;
	SINDRangeSetupSize(ndrange, global_size, local_size, work_dim);
	opencl_debug("\tndrange address space index = %d\n", 
		ndrange->address_space_index);

	/* Copy user elements from kernel to ND-Range */
	user_element_count = SIBinaryDictEntryGetNumUserElements(si_dict_entry);
	user_elements = SIBinaryDictEntryGetUserElements(si_dict_entry);
	ndrange->userElementCount = user_element_count;
	for (i = 0; i < user_element_count; i++)
		ndrange->userElements[i] = user_elements[i];

	/* Set up instruction memory */
	/* Initialize wavefront instruction buffer and PC */
	const char *text_buffer = SIBinaryDictEntryGetTextBuffer(si_dict_entry);
	unsigned int text_size = SIBinaryDictEntryGetTextSize(si_dict_entry);
	if (!text_size)
		fatal("%s: cannot load kernel code", __FUNCTION__);

	SINDRangeSetupInstMem(ndrange, text_buffer, text_size, 0);

	if (si_gpu)
		SIGpuMapNDRange(si_gpu, ndrange);
	
	opencl_debug("\tcopying %d arguments from the kernel\n", 
		kernel->arg_list->count);

	/* Copy kernel arg list to nd-range */
	ListForEach(kernel->arg_list, arg, SIArg)
	{
		arg_copy = SIArgCopy(arg);
		ListAdd(ndrange->arg_list, asObject(arg_copy));
	}

	list_add(driver->si_ndrange_list, ndrange);

	/* Return ID of new nd-range */
	return ndrange->id;
}




/*
 * OpenCL ABI call #15 - si_ndrange_get_num_buffer_entries
 *
 * Returns the number of available buffer entries in the waiting 
 * work-group queue.
 *
 * @param unsigned int *host_ptr
 *
 *	Location to be populated with the number of available 
 *	buffer entry slots.
 *
 * @return int
 *
 *	The function always returns 0.
 */


static int opencl_abi_si_ndrange_get_num_buffer_entries_impl(
	X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	X86Emu *x86_emu = ctx->emu;
	OpenclDriver *driver = x86_emu->opencl_driver;
	SIGpu *si_gpu = driver->si_gpu;

	unsigned int host_ptr;

	int available_buffer_entries;

	/* Arguments */
	host_ptr = regs->ecx;

	if (si_gpu)
	{
		available_buffer_entries = 
			SI_DRIVER_MAX_WORK_GROUP_BUFFER_SIZE -
			list_count(si_gpu->waiting_work_groups);
	}
	else
	{
		available_buffer_entries = 
			SI_DRIVER_MAX_WORK_GROUP_BUFFER_SIZE;
	}

	opencl_debug("\tavailable buffer entries = %d\n", 
		available_buffer_entries);

	mem_write(mem, host_ptr, sizeof available_buffer_entries,
		&available_buffer_entries);

	return 0;
}

/*
 * OpenCL ABI call #16 - si_ndrange_send_work_groups
 *
 * Let's the driver know that work groups have been added to 
 * the queue.
 *
 * @param unsigned int ndrange_id
 *
 *	ID of the ND-Range
 *
 * @param unsigned int work_group_start[3]
 *
 *	Origin of work groups to enqueue
 *
 * @param unsigned int work_group_count[3]
 *
 *	Count of work groups to enqueue
 *
 * @param unsigned int work_group_sizes[3]
 *
 * 	Overall sizes of work groups in each dimension
 *
 * @return int
 *
 *	The function always returns 0.
 */

static int opencl_abi_si_ndrange_send_work_groups_can_wakeup(
	X86Context *ctx, void *user_data)
{
	assert(user_data);
	SINDRange *ndrange = (SINDRange *) user_data;

	return !list_count(ndrange->waiting_work_groups);
}

static void opencl_abi_si_ndrange_send_work_groups_wakeup(
	X86Context *ctx, void *user_data)
{
	assert(user_data);
	SINDRange *ndrange = (SINDRange *) user_data;

	assert(!list_count(ndrange->waiting_work_groups));

	return;
}

static int opencl_abi_si_ndrange_send_work_groups_impl(X86Context *ctx)
{
	X86Emu *emu = ctx->emu;
	OpenclDriver *driver = emu->opencl_driver;
	SINDRange *ndrange = NULL, *tmp;

	struct x86_regs_t *regs = ctx->regs;
	struct mem_t *mem = ctx->mem;

	int i, j, k;
	int index;
	int ndrange_id;

	unsigned int work_group_start_ptr;
	unsigned int work_group_count_ptr;
	unsigned int work_group_sizes_ptr;
	unsigned int work_group_start[3];
	unsigned int work_group_count[3];
	unsigned int work_group_sizes[3];
	unsigned int total_num_groups;

	long work_group_id;

	/* Arguments */
	ndrange_id = regs->ecx;
	work_group_start_ptr = regs->edx;
	work_group_count_ptr = regs->esi;
	work_group_sizes_ptr = regs->edi;

	LIST_FOR_EACH(driver->si_ndrange_list, index)
	{
		tmp = (SINDRange* )list_get(driver->si_ndrange_list, index);
		if (tmp->id == ndrange_id)
			ndrange = tmp;
	}
	if (!ndrange)
		fatal("%s: invalid ndrange ID (%d)", __FUNCTION__, ndrange_id);
	opencl_debug("\tndrange %d\n", ndrange->id);

	mem_read(mem, work_group_start_ptr, 3 * 4, work_group_start);
	mem_read(mem, work_group_count_ptr, 3 * 4, work_group_count);
	mem_read(mem, work_group_sizes_ptr, 3 * 4, work_group_sizes);

	total_num_groups = work_group_count[2] * work_group_count[1] * 
		work_group_count[0];
	assert(total_num_groups <= SI_DRIVER_MAX_WORK_GROUP_BUFFER_SIZE -
		list_count(ndrange->waiting_work_groups));

	opencl_debug("\treceiving %d work groups: (%d,%d,%d) through (%d,%d,%d)\n",
		work_group_count[2] * work_group_count[1] * work_group_count[0],
		work_group_start[0], work_group_start[1], work_group_start[2],
		work_group_start[0] + work_group_count[0] - 1, 
		work_group_start[1] + work_group_count[1] - 1, 
		work_group_start[2] + work_group_count[2] - 1);

	/* Receive work groups (add them to the waiting queue) */
	for (i = work_group_start[2]; i < work_group_start[2] + work_group_count[2]; i++)
	{
		for (j = work_group_start[1]; j < work_group_start[1] + work_group_count[1]; j++)
		{
			for (k = work_group_start[0]; k < work_group_start[0] + work_group_count[0]; k++)
			{
				work_group_id = (i * work_group_sizes[1] * 
					work_group_sizes[0]) + (j * 
					work_group_sizes[0]) + k;

				list_enqueue(ndrange->waiting_work_groups, 
					(void*)work_group_id);
			}
		}
	}

	/* Suspend x86 context until driver needs more work */
	X86ContextSuspend(ctx, 
		opencl_abi_si_ndrange_send_work_groups_can_wakeup, 
		ndrange, opencl_abi_si_ndrange_send_work_groups_wakeup, 
		ndrange);

	return 0;
}

/*
 * OpenCL ABI call #17 - si_ndrange_finish
 *
 * Tells the driver that there are no more work groups to execute
 * from the ND-Range.
 *
 * @param int ndrange_id
 *
 *	ID of nd-range
 *
 * @return int
 *
 *	The function always returns 0.
 */

static int opencl_abi_si_ndrange_finish_can_wakeup(X86Context *ctx, 
	void *user_data)
{
	assert(user_data);
	SINDRange *ndrange = (SINDRange *) user_data;

	assert(ndrange->last_work_group_sent);
	
	int can_wakeup =
		!list_count(ndrange->waiting_work_groups) &&
		!list_count(ndrange->running_work_groups);

	return can_wakeup;
}

static void opencl_abi_si_ndrange_finish_wakeup(X86Context *ctx, 
	void *user_data)
{
	assert(user_data);

	SINDRange *ndrange = (SINDRange *) user_data;

	assert(!list_count(ndrange->waiting_work_groups));
	assert(!list_count(ndrange->running_work_groups));
	assert(ndrange->last_work_group_sent);

	return;
}

static int opencl_abi_si_ndrange_finish_impl(X86Context *ctx)
{
	X86Emu *emu = ctx->emu;
	OpenclDriver *driver = emu->opencl_driver;
	struct x86_regs_t *regs = ctx->regs;

	SINDRange *ndrange = NULL, *tmp;

	int ndrange_id = regs->ecx;

	int index;

	LIST_FOR_EACH(driver->si_ndrange_list, index)
	{
		tmp = (SINDRange* )list_get(driver->si_ndrange_list, index);
		if (tmp->id == ndrange_id)
			ndrange = tmp;
	}
	if (!ndrange)
		fatal("%s: invalid ndrange ID (%d)", __FUNCTION__, ndrange_id);

	ndrange->last_work_group_sent = 1;
	
	/* If no work-groups are left in the queues, remove the nd-range
	 * from the driver list */
	if (!list_count(ndrange->running_work_groups) && 
		!list_count(ndrange->waiting_work_groups))
	{
		opencl_debug("\tnd-range %d finished\n", ndrange_id);
	}
	else
	{
		opencl_debug("\twaiting for nd-range %d to finish (blocking)\n", 
				ndrange_id);
		X86ContextSuspend(ctx, 
			opencl_abi_si_ndrange_finish_can_wakeup, ndrange, 
			opencl_abi_si_ndrange_finish_wakeup, ndrange);
	}

	return 0;
}

/*
 * OpenCL ABI call #18 - si_ndrange_pass_mem_objs
 *
 * @param int ndrange_id
 *
 *	ID of nd-range
 *
 * @param int kernel_id
 *
 *	ID of kernel
 *
 * @param unsigned int *tables_ptr
 *
 *	Location reserved for internal tables (may not be aligned)
 *
 * @param unsigned int *constant_buffers_ptr
 *
 *	Location reserved for constant buffers (may not be aligned)
 *
 * @return int
 *
 *	The function always returns 0.
 */

static int opencl_abi_si_ndrange_pass_mem_objs_impl(X86Context *ctx)
{
	X86Emu *emu = ctx->emu;
	OpenclDriver *driver = emu->opencl_driver;
	SIGpu *si_gpu = driver->si_gpu;
	SINDRange *ndrange = NULL, *tmp_ndrange;

	struct opencl_si_kernel_t *kernel;
	struct x86_regs_t *regs = ctx->regs;

	unsigned int tables_ptr;
	unsigned int constant_buffers_ptr;

	int index;
	int ndrange_id;
	int kernel_id;

	ndrange_id = regs->ecx;
	kernel_id = regs->edx;

	LIST_FOR_EACH(driver->si_ndrange_list, index)
	{
		tmp_ndrange = (SINDRange* )list_get(driver->si_ndrange_list, 
			index);
		if (tmp_ndrange->id == ndrange_id)
			ndrange = tmp_ndrange;
	}
	if (!ndrange)
		fatal("%s: invalid ndrange ID (%d)", __FUNCTION__, ndrange_id);

	kernel = list_get(driver->si_kernel_list, kernel_id);
	if (!kernel)
		fatal("%s: invalid kernel ID (%d)", __FUNCTION__, kernel_id);

	if (driver->fused)
	{
		/* 16 extra bytes allocated */
		tables_ptr = (regs->esi + 15) & 0xFFFFFFF0;
		constant_buffers_ptr = (regs->edi + 15) & 0xFFFFFFF0;

		ndrange->const_buf_table = tables_ptr;

		/* The successive tables must be aligned */
		ndrange->resource_table = (ndrange->const_buf_table + 
			SI_EMU_CONST_BUF_TABLE_SIZE + 16) & 0xFFFFFFF0;
		
		ndrange->uav_table = (ndrange->resource_table +
			SI_EMU_RESOURCE_TABLE_SIZE + 16) & 0xFFFFFFF0;

		ndrange->cb_start = constant_buffers_ptr;
		
		opencl_si_ndrange_setup_mmu(ndrange, driver->x86_cpu->mmu, 
			ctx->address_space_index, si_gpu->mmu, tables_ptr, 
			constant_buffers_ptr);
	}
	else
	{
		if (si_gpu)
		{
			opencl_si_kernel_create_ndrange_tables(ndrange, 
				si_gpu->mmu); 
			opencl_si_kernel_create_ndrange_constant_buffers(
				ndrange, si_gpu->mmu); 
		}
		else
		{
			opencl_si_kernel_create_ndrange_tables(ndrange, NULL); 
			opencl_si_kernel_create_ndrange_constant_buffers(
				ndrange, NULL); 
		}
	}
	opencl_si_kernel_setup_ndrange_constant_buffers(ndrange);
	opencl_si_kernel_setup_ndrange_args(kernel, ndrange);
	opencl_si_kernel_debug_ndrange_state(kernel, ndrange);

	return 0;
}

/*
 * OpenCL ABI call #19 - si_ndrange_set_fused
 *
 * @param unsigned int fused
 *
 *	Whether to enable or disable the fused device
 *
 * @return int
 *
 *	The function always returns 0.
 */

static int opencl_abi_si_ndrange_set_fused_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;

	X86Emu *x86_emu = ctx->emu;
	OpenclDriver *driver = x86_emu->opencl_driver;
	SIGpu *si_gpu = driver->si_gpu;

	driver->fused = regs->ecx;

	/* With a fused device, the GPU MMU will be initialized by
	 * the CPU */
	if (driver->fused)
	{
		opencl_debug("\tfused\n");
		assert(si_gpu);
		si_gpu->mmu->read_only = 1;
	}
	else
	{
		opencl_debug("\tnot fused\n");
	}

	return 0;
}

/*
 * OpenCL ABI call #20 - si_ndrange_flush
 *
 * @param int ndrange-id
 *
 *	ID of ND-Range to flush
 *
 * @return int
 *
 *	The function always returns 0.
 */

static int opencl_abi_si_ndrange_flush_can_wakeup(X86Context *ctx, 
	void *user_data)
{
	assert(user_data);
	
	int* witness_ptr = user_data;
	int can_wakeup = !(*witness_ptr);

	return can_wakeup;
}

static void opencl_abi_si_ndrange_flush_wakeup(X86Context *ctx, 
	void *user_data)
{
	assert(user_data);

	int* witness_ptr = user_data;
	assert(!(*witness_ptr));

	return;
}

static int opencl_abi_si_ndrange_flush_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	X86Emu *x86_emu = ctx->emu;
	OpenclDriver *driver = x86_emu->opencl_driver;
	SIGpu *si_gpu = driver->si_gpu;

	/* If there's not a timing simulator, no need to flush */
	if (!si_gpu)
		return 0;

	SINDRange *ndrange = NULL, *tmp_ndrange;

	int index;
	int ndrange_id;

	ndrange_id = regs->ecx;

	LIST_FOR_EACH(driver->si_ndrange_list, index)
	{
		tmp_ndrange = (SINDRange* )list_get(driver->si_ndrange_list, 
			index);
		if (tmp_ndrange->id == ndrange_id)
			ndrange = tmp_ndrange;
	}
	if (!ndrange)
		fatal("%s: invalid ndrange ID (%d)", __FUNCTION__, ndrange_id);

	opencl_debug("\tndrange %d\n", ndrange->id);

	/* Flush RW or WO buffers from this ND-Range */
	opencl_si_kernel_flush_ndrange_buffers(ndrange, si_gpu, x86_emu);

	X86ContextSuspend(ctx, opencl_abi_si_ndrange_flush_can_wakeup, 
		&(ndrange->flushing), opencl_abi_si_ndrange_flush_wakeup, 
		&(ndrange->flushing));

	return 0;
}

/*
 * OpenCL ABI call #21 - si_ndrange_free
 *
 * @param int ndrange-id
 *
 *	ID of ND-Range to free
 *
 * @return int
 *
 *	The function always returns 0.
 */

static int opencl_abi_si_ndrange_free_impl(X86Context *ctx)
{
	struct x86_regs_t *regs = ctx->regs;
	X86Emu *x86_emu = ctx->emu;
	OpenclDriver *driver = x86_emu->opencl_driver;

	SINDRange *ndrange = NULL, *tmp_ndrange;

	int index;
	int ndrange_id;

	ndrange_id = regs->ecx;

	/* Check for nd-range in the driver's list */
	LIST_FOR_EACH(driver->si_ndrange_list, index)
	{
		tmp_ndrange = (SINDRange* )list_get(driver->si_ndrange_list, 
			index);
		if (tmp_ndrange->id == ndrange_id)
			ndrange = tmp_ndrange;
	}
	if (!ndrange)
		fatal("%s: invalid ndrange ID (%d)", __FUNCTION__, ndrange_id);

	/* Free */
	list_remove(driver->si_ndrange_list, ndrange);
	delete(ndrange);

	return 0;
}


/*
 * OpenCL ABI call #22 - ndrange_start
 *
 * Tell the driver that an nd-range (for any device) has
 * started executing. 
 *
 * @return int
 *
 *	The function always returns 0.
 */

static int opencl_abi_ndrange_start_impl(X86Context *ctx)
{
	X86Emu *x86_emu = ctx->emu;
	OpenclDriver *driver = x86_emu->opencl_driver;

	assert(driver->ndranges_running >= 0);
	driver->ndranges_running++;

	if (driver->x86_cpu)
		driver->x86_cpu->ndranges_running++;

	return 0;
}


/*
 * OpenCL ABI call #23 - ndrange_end
 *
 * Tell the driver that an nd-range (for any device) has
 * finished executing. 
 *
 * @return int
 *
 *	The function always returns 0.
 */

static int opencl_abi_ndrange_end_impl(X86Context *ctx)
{
	X86Emu *x86_emu = ctx->emu;
	OpenclDriver *driver = x86_emu->opencl_driver;

	driver->ndranges_running--;
	assert(driver->ndranges_running >= 0);

	if (driver->x86_cpu)
	{
		driver->x86_cpu->ndranges_running--;
		assert(driver->ndranges_running >= 0);
	}

	return 0;
}

#endif
	
}  // namespace SIDriver


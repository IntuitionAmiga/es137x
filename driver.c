/*
 * Copyright 2007 Haiku Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Bek, host.haiku@gmx.de
 *      Zayn Otley, intuitionamiga@gmail.com
 */
#include "driver.h"

int32 api_version = B_CUR_DRIVER_API_VERSION;
device_t device;

status_t init_hardware(void) {
	dprintf("es137x_audio: %s\n", __func__);
	return B_OK;
}

status_t init_driver(void) {
	dprintf("es137x_audio: %s\n", __func__);
	device.running = false;
	return B_OK;
}

void uninit_driver(void) {
}

const char** publish_devices(void) {
	static const char* published_paths[] = {
		MULTI_AUDIO_DEV_PATH "/es137x/0", NULL
	};
	dprintf("es137x_audio: %s\n", __func__);

	return published_paths;
}

static status_t es137x_audio_open (const char *name, uint32 flags, void** cookie) {
	dprintf("es137x_audio: %s\n" , __func__ );
	*cookie = &device;
	return B_OK;
}

static status_t es137x_audio_read (void* cookie, off_t a, void* b, size_t* num_bytes) {
	dprintf("es137x_audio: %s\n" , __func__ );
	// Audio drivers are not supposed to return anything
	// inside here
	*num_bytes = 0;
	return B_IO_ERROR;
}

static status_t es137x_audio_write (void* cookie, off_t a, const void* b, size_t* num_bytes) {
	dprintf("es137x_audio: %s\n" , __func__ );
	// Audio drivers are not supposed to return anything
	// inside here
	*num_bytes = 0;
	return B_IO_ERROR;
}

static status_t es137x_audio_control (void* cookie, uint32 op, void* arg, size_t len) {
	//dprintf("es137x_audio: %s\n" , __func__ );
	// In case we have a valid cookie, initialized
	// the driver and hardware connection properly
	// Simply pass through to the multi audio hooks
	if (cookie)
		return multi_audio_control(cookie, op, arg, len);
	else
		dprintf("es137x_audio: %s called without cookie\n" , __func__);

	// Return error in case we have no valid setup
	return B_BAD_VALUE;
}

static status_t es137x_audio_close (void* cookie) {
	device_t* device = (device_t*) cookie;
	dprintf("es137x_audio: %s\n" , __func__ );
	if (device && device->running)
		es137x_stop_hardware(device);
	return B_OK;
}


static status_t es137x_audio_free (void* cookie) {
	dprintf("es137x_audio: %s\n" , __func__ );
	return B_OK;
}

device_hooks driver_hooks = {
	es137x_audio_open,
	es137x_audio_close,
	es137x_audio_free,
	es137x_audio_control,
	es137x_audio_read,
	es137x_audio_write
};

device_hooks* find_device(const char* name) {
	return &driver_hooks;
}

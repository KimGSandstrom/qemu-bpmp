#ifndef HW_NVIDIA_GPIO_GUEST_H
#define HW_NVIDIA_GPIO_GUEST_H

#include "qom/object.h"

DeviceState *nvidia_gpio_guest_create(hwaddr);


/* Important note:
 * the struct below is copied from gpio-virt code file drivers/gpio-host-proxy/gpio-host-proxy.h
 * make sure the copy is up to date
 */

enum tegra_gpio_signal {
	GPIO_READ = 'r',
	GPIO_WRITE = 'w',
	GPIO_INPUT = 'i',
	GPIO_TRISTATE = 't',
	GPIO_DIRECTION = 'd',
	GPIO_MUX = 'm'
};

_Static_assert(sizeof(enum tegra_gpio_signal) == 4,
               "Enum size failure\n");

struct tegra_gpio_op {
	void  *io_address;		// Defined by bank and register. (void __iomem *) in kernel module
	enum tegra_gpio_signal signal;	// taking values 'r' or 'w' to define desired operation
	uint32_t value;			// Read or write value
	uint32_t bank;			// Memory bank
	uint32_t reg;			// Register (offset)
};

_Static_assert( (sizeof(struct tegra_gpio_op) % 8) == 0,
               "tegra_gpio_io not aligned to 64 bits\n");

#endif

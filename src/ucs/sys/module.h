/**
 * Copyright (C) Mellanox Technologies Ltd. 2001-2018.  ALL RIGHTS RESERVED.
 *
 * See file LICENSE for terms.
 */


#ifndef UCS_MODULE_H_
#define UCS_MODULE_H_

#include <ucs/type/init_once.h>


/**
 * Declare a "framework", which is a context for a specific collection of
 * loadable modules. Usually the modules in a particular framework provide
 * alternative implementations of the same internal interface.
 *
 * @param [in] _name  Framework name (as a token)
 */
#define UCS_MODULE_FRAMEWORK_DECLARE(_name) \
    static ucs_init_once_t ucs_framework_init_once_##_name = \
        UCS_INIT_ONCE_INIITIALIZER


/**
 * Load all modules in a particular framework.
 *
 * The modules in the framework are loaded by dlopen(). The shared library name
 * of a module is: "lib<framework>_<module>.so.<version>", where:
 * - <framework> is the framework name
 * - <module> is the module name. The list of all modules in a framework is
 *   defined by the preprocessor macro <framework>_MODULES in the auto-generated
 *   config.h file, for example: #define foo_MODULES ":bar1:bar2".
 * - <version> is the shared library version of the module, as generated by
 *   libtool. It's extracted from the full path of the current library (libucs).
 *
 * Module shared libraries are searched in the following locations (in order of
 * priority):
 *  1. 'ucx' sub-directory inside the directory of the current shared library (libucs)
 *  2. ${libdir}/ucx, where ${libdir} is the directory where libraries are installed
 * Note that if libucs is loaded from its installation path, (1) and (2) are the
 * same location. Only if libucs is moved or ran from build directory, the paths
 * will be different, in which case we prefer the 'local' library rather than the
 * 'installed' one.
 *
 * @param [in] _name  Framework name (as a token)
 */
#define UCS_MODULE_FRAMEWORK_LOAD(_name) \
    ucs_load_modules(#_name, _name##_MODULES, &ucs_framework_init_once_##_name)


/**
 * Internal function. Please use @ref UCS_MODULE_FRAMEWORK_LOAD macro instead.
 */
void ucs_load_modules(const char *framework, const char *modules,
                      ucs_init_once_t *init_once);


#endif

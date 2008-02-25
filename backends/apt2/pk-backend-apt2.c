/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2007 Ali Sabil <ali.sabil@gmail.com>
 * Copyright (C) 2007 Tom Parker <palfrey@tevp.net>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <pk-network.h>
#include <pk-backend.h>
#include <pk-backend-dbus.h>

static PkBackendDbus *dbus;
static PkNetwork *network;

#define PK_DBUS_BACKEND_SERVICE_APT   "org.freedesktop.PackageKitAptBackend"

/**
 * backend_initialize:
 * This should only be run once per backend load, i.e. not every transaction
 */
static void
backend_initialize (PkBackend *backend)
{
	g_return_if_fail (backend != NULL);
	pk_debug ("FILTER: initialize");
	network = pk_network_new ();
	dbus = pk_backend_dbus_new ();
	pk_backend_dbus_set_name (dbus, PK_DBUS_BACKEND_SERVICE_APT);
}

/**
 * backend_destroy:
 * This should only be run once per backend load, i.e. not every transaction
 */
static void
backend_destroy (PkBackend *backend)
{
	g_return_if_fail (backend != NULL);
	g_return_if_fail (dbus != NULL);
	pk_debug ("FILTER: destroy");
	g_object_unref (network);
	pk_backend_dbus_kill (dbus);
	g_object_unref (dbus);
}

/**
 * backend_get_groups:
 */
static void
backend_get_groups (PkBackend *backend, PkEnumList *elist)
{
	g_return_if_fail (backend != NULL);
	pk_enum_list_append_multiple (elist,
				      PK_GROUP_ENUM_ACCESSORIES,
				      PK_GROUP_ENUM_GAMES,
				      PK_GROUP_ENUM_GRAPHICS,
				      PK_GROUP_ENUM_INTERNET,
				      PK_GROUP_ENUM_OFFICE,
				      PK_GROUP_ENUM_OTHER,
				      PK_GROUP_ENUM_PROGRAMMING,
				      PK_GROUP_ENUM_MULTIMEDIA,
				      PK_GROUP_ENUM_SYSTEM,
				      -1);
}

/**
 * backend_get_filters:
 */
static void
backend_get_filters (PkBackend *backend, PkEnumList *elist)
{
	g_return_if_fail (backend != NULL);
	pk_enum_list_append_multiple (elist,
				      PK_FILTER_ENUM_GUI,
				      PK_FILTER_ENUM_INSTALLED,
				      PK_FILTER_ENUM_DEVELOPMENT,
				      -1);
}

/**
 * pk_backend_bool_to_text:
 *
static const gchar *
pk_backend_bool_to_text (gboolean value)
{
	if (value == TRUE) {
		return "yes";
	}
	return "no";
} */

/**
 * backend_get_depends:
 *
static void
backend_get_depends (PkBackend *backend, const gchar *package_id, gboolean recursive)
{
	g_return_if_fail (backend != NULL);
	g_return_if_fail (spawn != NULL);
	pk_backend_spawn_helper (spawn, "get-depends.py", package_id, pk_backend_bool_to_text (recursive), NULL);
} */

/**
 * backend_get_updates:
 */
static void
backend_get_updates (PkBackend *backend)
{
	g_return_if_fail (backend != NULL);
	g_return_if_fail (dbus != NULL);
	pk_backend_dbus_get_updates (dbus);
} 

/**
 * backend_install_package:
 *
static void
backend_install_package (PkBackend *backend, const gchar *package_id)
{
	g_return_if_fail (backend != NULL);
	g_return_if_fail (spawn != NULL);

	// check network state 
	if (pk_network_is_online (network) == FALSE) {
		pk_backend_error_code (backend, PK_ERROR_ENUM_NO_NETWORK, "Cannot install when offline");
		pk_backend_finished (backend);
		return;
	}

	pk_backend_spawn_helper (spawn, "install.py", package_id, NULL);
} */

/**
 * backend_refresh_cache:
 *
static void
backend_refresh_cache (PkBackend *backend, gboolean force)
{
	g_return_if_fail (backend != NULL);
	g_return_if_fail (spawn != NULL);

	// check network state
	if (pk_network_is_online (network) == FALSE) {
		pk_backend_error_code (backend, PK_ERROR_ENUM_NO_NETWORK, "Cannot refresh cache whilst offline");
		pk_backend_finished (backend);
		return;
	}

	pk_backend_spawn_helper (spawn, "refresh-cache.py", NULL);
} */

/**
 * pk_backend_remove_package:
 *
static void
backend_remove_package (PkBackend *backend, const gchar *package_id, gboolean allow_deps)
{
	g_return_if_fail (backend != NULL);
	g_return_if_fail (spawn != NULL);
	pk_backend_spawn_helper (spawn, "remove.py", pk_backend_bool_to_text (allow_deps), package_id, NULL);
} */

/**
 * pk_backend_update_package:
 *
static void
backend_update_package (PkBackend *backend, const gchar *package_id)
{
	g_return_if_fail (backend != NULL);
	g_return_if_fail (spawn != NULL);

	// check network state
	if (pk_network_is_online (network) == FALSE) {
		pk_backend_error_code (backend, PK_ERROR_ENUM_NO_NETWORK, "Cannot install when offline");
		pk_backend_finished (backend);
		return;
	}

	pk_backend_spawn_helper (spawn, "update.py", package_id, NULL);
} */

/**
 * pk_backend_update_system:
 *
static void
backend_update_system (PkBackend *backend)
{
	g_return_if_fail (backend != NULL);
	g_return_if_fail (spawn != NULL);
	pk_backend_spawn_helper (spawn, "update-system.py", NULL);
} */

/**
 * pk_backend_resolve:
 *
static void
backend_resolve (PkBackend *backend, const gchar *filter, const gchar *package_id)
{
	g_return_if_fail (backend != NULL);
	g_return_if_fail (spawn != NULL);
	pk_backend_spawn_helper (spawn, "resolve.py", filter, package_id, NULL);
} */

/**
 * pk_backend_get_repo_list:
 *
static void
backend_get_repo_list (PkBackend *backend)
{
	g_return_if_fail (backend != NULL);
	g_return_if_fail (spawn != NULL);
	pk_backend_spawn_helper (spawn, "get-repo-list.py", NULL);
} */

/**
 * backend_get_description:
 *  */
static void
backend_get_description (PkBackend *backend, const gchar *package_id)
{
        g_return_if_fail (backend != NULL);
        g_return_if_fail (dbus != NULL);
        pk_backend_dbus_get_description (dbus, package_id);
}

/**
 *  * pk_backend_search_details:
 *   */
static void
backend_search_details (PkBackend *backend, const gchar *filter, const gchar *search)
{
        g_return_if_fail (backend != NULL);
        g_return_if_fail (dbus != NULL);
        pk_backend_dbus_search_details (dbus, filter, search);
}

/**
 *  * pk_backend_search_name:
 *   */
static void
backend_search_name (PkBackend *backend, const gchar *filter, const gchar *search)
{
        g_return_if_fail (backend != NULL);
        g_return_if_fail (dbus != NULL);
        pk_backend_dbus_search_name (dbus, filter, search);
}

PK_BACKEND_OPTIONS (
	"Apt",					/* description */
	"Ali Sabil <ali.sabil@gmail.com>; Tom Parker <palfrey@tevp.net>; Sebastian Heinlein <glatzor@ubuntu.com>",	/* author */
	backend_initialize,			/* initalize */
	backend_destroy,			/* destroy */
	backend_get_groups,			/* get_groups */
	backend_get_filters,			/* get_filters */
	NULL,					/* cancel */
	NULL,					/* get_depends */
	backend_get_description,	        /* get_description */
	NULL,					/* get_files */
	NULL,					/* get_requires */
	NULL,					/* get_update_detail */
	backend_get_updates,			/* get_updates */
	NULL,					/* install_package */
	NULL,					/* install_file */
	NULL,					/* refresh_cache */
	NULL,					/* remove_package */
	NULL,					/* resolve */
	NULL,					/* rollback */
	backend_search_details,			/* search_details */
	NULL,					/* search_file */
	NULL,					/* search_group */
	backend_search_name,			/* search_name */
	NULL,					/* update_package */
	NULL,					/* update_system */
	NULL,					/* get_repo_list */
	NULL,					/* repo_enable */
	NULL,					/* repo_set_data */
	NULL					/* service_pack */
);

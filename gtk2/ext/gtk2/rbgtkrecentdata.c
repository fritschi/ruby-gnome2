/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2011  Ruby-GNOME2 Project Team
 *  Copyright (C) 2006  Masao Mutoh
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#include "global.h"

#if GTK_CHECK_VERSION(2,10,0)

/*****************************************/
static GtkRecentData*
rd_copy(const GtkRecentData* data)
{
    GtkRecentData* new_data;
    g_return_val_if_fail (data != NULL, NULL);
    new_data = g_new(GtkRecentData, 1);
    *new_data = *data;
    return new_data;
}

static void
rd_free(GtkRecentData* boxed)
{
    if (boxed){
        g_free(boxed->groups);
        g_free(boxed);
    }
}

GType
gtk_recent_data_get_type(void)
{
  static GType our_type = 0;
  if (our_type == 0)
    our_type = g_boxed_type_register_static ("GtkRecentData",
                    (GBoxedCopyFunc)rd_copy,
                    (GBoxedFreeFunc)rd_free);
  return our_type;
}
/*****************************************/

#define _SELF(w) ((GtkRecentData*)RVAL2BOXED(w, GTK_TYPE_RECENT_DATA))

static VALUE
rd_initialize(VALUE self)
{   
    GtkRecentData data;
    G_INITIALIZE(self, &data);
    return Qnil;
}

#define RD_STR(name)\
static VALUE \
rd_get_ ## name (VALUE self)\
{\
    return CSTR2RVAL(_SELF(self)->name);\
}\
static VALUE \
rd_set_ ## name (VALUE self, VALUE val)\
{\
    _SELF(self)->name = (gchar *)RVAL2CSTR(val);\
    return self;\
}

RD_STR(display_name);
RD_STR(description);
RD_STR(mime_type);
RD_STR(app_name);
RD_STR(app_exec);

static VALUE
rd_get_groups(VALUE self)
{
    gchar** grps = _SELF(self)->groups;
    VALUE ary = rb_ary_new();
 
    gint i = 0;
    while (grps[i]) {
        rb_ary_push(ary, CSTR2RVAL((gchar*)grps[i]));
        i++;
    }
    return ary;
}

static VALUE
rd_set_groups(VALUE self, VALUE groups)
{
    _SELF(self)->groups = RVAL2STRV_DUP(groups);

    return self;
}

static VALUE
rd_get_is_private(VALUE self)
{
    return CBOOL2RVAL(_SELF(self)->is_private);
}

static VALUE
rd_set_is_private(VALUE self, VALUE is_private)
{
    _SELF(self)->is_private = RVAL2CBOOL(is_private);
    return self;
}

#endif

void
Init_gtk_recent_data(void)
{
#if GTK_CHECK_VERSION(2,10,0)
    VALUE rd = G_DEF_CLASS(GTK_TYPE_RECENT_DATA, "RecentData", mGtk);

    rb_define_method(rd, "initialize", rd_initialize, 0);
    rb_define_method(rd, "display_name", rd_get_display_name, 0);
    rb_define_method(rd, "set_display_name", rd_set_display_name, 1);
    rb_define_method(rd, "description", rd_get_description, 0);
    rb_define_method(rd, "set_description", rd_set_description, 1);
    rb_define_method(rd, "mime_type", rd_get_mime_type, 0);
    rb_define_method(rd, "set_mime_type", rd_set_mime_type, 1);
    rb_define_method(rd, "app_name", rd_get_app_name, 0);
    rb_define_method(rd, "set_app_name", rd_set_app_name, 1);
    rb_define_method(rd, "app_exec", rd_get_app_exec, 0);
    rb_define_method(rd, "set_app_exec", rd_set_app_exec, 1);
    rb_define_method(rd, "groups", rd_get_groups, 0);
    rb_define_method(rd, "set_groups", rd_set_groups, 1);
    rb_define_method(rd, "private?", rd_get_is_private, 0);
    rb_define_method(rd, "set_private", rd_set_is_private, 1);

    G_DEF_SETTERS(rd);   
#endif
}

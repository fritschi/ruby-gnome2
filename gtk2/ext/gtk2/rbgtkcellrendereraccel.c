/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2011  Ruby-GNOME2 Project Team
 *  Copyright (C) 2006  Ruby-GNOME2 Team
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

#define _SELF(s) (GTK_CELL_RENDERER_ACCEL(RVAL2GOBJ(s)))

static VALUE
craccel_initialize(VALUE self)
{
    RBGTK_INITIALIZE(self, gtk_cell_renderer_accel_new());
    return Qnil;
}

#endif

void
Init_gtk_cellrendereraccel(void)
{
#if GTK_CHECK_VERSION(2,10,0)
    VALUE renderer = G_DEF_CLASS(GTK_TYPE_CELL_RENDERER_ACCEL, "CellRendererAccel", mGtk);
    rb_define_method(renderer, "initialize", craccel_initialize, 0);

    /* GtkCellRendererAccelMode */
    G_DEF_CLASS(GTK_TYPE_CELL_RENDERER_ACCEL_MODE, "Mode", renderer);
    G_DEF_CONSTANTS(renderer, GTK_TYPE_CELL_RENDERER_ACCEL_MODE, "GTK_CELL_RENDERER_ACCEL_");
#endif
}


 

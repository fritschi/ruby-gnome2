# Copyright (C) 2015  Ruby-GNOME2 Project Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

module Gtk
  class RecentChooserDialog
    alias_method :initialize_raw, :initialize
    def initialize(options={})
      initialize_options = {
        :recent_manager => options[:recent_manager],
      }
      gobject_initialize = GLib::Object.instance_method(:initialize).bind(self)
      gobject_initialize.call(initialize_options)
      Loader.reference_gobject(self, :sink => true)

      title = options[:title]
      parent = options[:parent]
      buttons = options[:buttons]

      set_title(title) if title
      set_transient_for(parent) if parent

      add_buttons(*buttons) if buttons
    end
  end
end

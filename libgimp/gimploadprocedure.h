/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimploadprocedure.h
 * Copyright (C) 2019 Michael Natterer <mitch@gimp.org>
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <https://www.gnu.org/licenses/>.
 */

#ifndef __GIMP_LOAD_PROCEDURE_H__
#define __GIMP_LOAD_PROCEDURE_H__

#include <libgimp/gimpfileprocedure.h>

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


/**
 * GimpRunLoadFunc:
 * @procedure:   the [class@Gimp.Procedure] that runs.
 * @run_mode:    the [enum@RunMode].
 * @file:        the [iface@Gio.File] to load from.
 * @metadata:    the [class@Gimp.Metadata] which will be added to the new image.
 * @flags: (inout): flags to filter which metadata will be added..
 * @config:      the @procedure's remaining arguments.
 * @run_data: (closure): the run_data given in gimp_load_procedure_new().
 *
 * The load function is run during the lifetime of the GIMP session, each time a
 * plug-in load procedure is called.
 *
 * You are expected to read @file and create a [class@Gimp.Image] out of its
 * data. This image will be the first return value.
 * @metadata will be filled from metadata from @file if our infrastructure
 * supports this format. You may tweak this object, for instance adding metadata
 * specific to the format. You can also edit @flags if you need to filter out
 * some specific common fields. For instance, it is customary to remove a
 * colorspace field with [flags@MetadataLoadFlags] when a profile was added.
 *
 * Returns: (transfer full): the @procedure's return values.
 *
 * Since: 3.0
 **/
typedef GimpValueArray * (* GimpRunLoadFunc) (GimpProcedure         *procedure,
                                              GimpRunMode            run_mode,
                                              GFile                 *file,
                                              GimpMetadata          *metadata,
                                              GimpMetadataLoadFlags *flags,
                                              GimpProcedureConfig   *config,
                                              gpointer               run_data);


#define GIMP_TYPE_LOAD_PROCEDURE            (gimp_load_procedure_get_type ())
#define GIMP_LOAD_PROCEDURE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LOAD_PROCEDURE, GimpLoadProcedure))
#define GIMP_LOAD_PROCEDURE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_LOAD_PROCEDURE, GimpLoadProcedureClass))
#define GIMP_IS_LOAD_PROCEDURE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LOAD_PROCEDURE))
#define GIMP_IS_LOAD_PROCEDURE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_LOAD_PROCEDURE))
#define GIMP_LOAD_PROCEDURE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_LOAD_PROCEDURE, GimpLoadProcedureClass))


typedef struct _GimpLoadProcedure        GimpLoadProcedure;
typedef struct _GimpLoadProcedureClass   GimpLoadProcedureClass;
typedef struct _GimpLoadProcedurePrivate GimpLoadProcedurePrivate;

struct _GimpLoadProcedure
{
  GimpFileProcedure         parent_instance;

  GimpLoadProcedurePrivate *priv;
};

struct _GimpLoadProcedureClass
{
  GimpFileProcedureClass parent_class;
};


GType           gimp_load_procedure_get_type             (void) G_GNUC_CONST;

GimpProcedure * gimp_load_procedure_new                  (GimpPlugIn        *plug_in,
                                                          const gchar       *name,
                                                          GimpPDBProcType    proc_type,
                                                          GimpRunLoadFunc    run_func,
                                                          gpointer           run_data,
                                                          GDestroyNotify     run_data_destroy);

void            gimp_load_procedure_set_handles_raw      (GimpLoadProcedure *procedure,
                                                          gboolean           handles_raw);
gboolean        gimp_load_procedure_get_handles_raw      (GimpLoadProcedure *procedure);

void            gimp_load_procedure_set_thumbnail_loader (GimpLoadProcedure *procedure,
                                                          const gchar       *thumbnail_proc);
const gchar   * gimp_load_procedure_get_thumbnail_loader (GimpLoadProcedure *procedure);

G_DEFINE_AUTOPTR_CLEANUP_FUNC (GimpLoadProcedure, g_object_unref);


G_END_DECLS

#endif  /*  __GIMP_LOAD_PROCEDURE_H__  */

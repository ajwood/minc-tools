/* ----------------------------- MNI Header -----------------------------------
@NAME       : gyro_to_minc.h
@DESCRIPTION: Header file for gyro_to_minc.h
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    : November 25, 1993 (Peter Neelin)
@MODIFIED   : $Log: gyro_to_minc.h,v $
@MODIFIED   : Revision 1.1  1993-11-30 14:42:43  neelin
@MODIFIED   : Initial revision
@MODIFIED   :
@COPYRIGHT  :
              Copyright 1993 Peter Neelin, McConnell Brain Imaging Centre, 
              Montreal Neurological Institute, McGill University.
              Permission to use, copy, modify, and distribute this
              software and its documentation for any purpose and without
              fee is hereby granted, provided that the above copyright
              notice appear in all copies.  The author and McGill University
              make no representations about the suitability of this
              software for any purpose.  It is provided "as is" without
              express or implied warranty.
---------------------------------------------------------------------------- */

#include <minc.h>

/* Default value for ncopts */
#define NCOPTS_DEFAULT NC_VERBOSE

/* Directory for output files (if names created internally). Note that
   the final "/" is necessary. */
#define OUTPUT_MINC_DIR "/usr/people/mritrans/images/"

/* Owner for newly created minc files */
#define MINC_FILE_OWNER 1100
#define MINC_FILE_GROUP 200

/* Possible MRI dimensions */
typedef enum { SLICE = 0, ECHO, TIME, PHASE, CHEM_SHIFT, MRI_NDIMS } Mri_Index;

/* World dimensions */
typedef enum { XCOORD = 0, YCOORD, ZCOORD, WORLD_NDIMS } World_Index;

/* Volume dimensions */
typedef enum { VSLICE = 0, VROW, VCOLUMN, VOL_NDIMS } Volume_Index;

/* Orientations */
typedef enum {TRANSVERSE = 0, SAGITTAL, CORONAL, NUM_ORIENTATIONS} Orientation;

/* String type */
typedef char Cstring[256];

/* Structure for general info about files */
typedef struct {
   int initialized;
   int nrows;
   int ncolumns;
   int size[MRI_NDIMS];        /* Size of dimension across these files */
   int first[MRI_NDIMS];       /* First in dimenion across these files */
   int total_size[MRI_NDIMS];  /* Size of dimension across acquisition */
   int *position[MRI_NDIMS];    /* Array indicating position of each image in
                                   output file. Only allocated when size > 1 */
   int image_index[MRI_NDIMS];  /* Mapping from MRI dim to output image dim */
   Orientation orientation;
   World_Index slice_world;
   World_Index row_world;
   World_Index column_world;
   double step[WORLD_NDIMS];
   double start[WORLD_NDIMS];
   double dircos[WORLD_NDIMS][WORLD_NDIMS];
   double slice_step;
   double slice_start;
   double slicepos_min;
   double slicepos_max;
   nc_type datatype;
   int is_signed;
   double pixel_min;
   double pixel_max;
   Cstring units;
   struct {
      Cstring name;
      Cstring identification;
      Cstring birth_date;
      Cstring sex;
      double weight;
   } patient;
   struct {
      Cstring start_time;
      Cstring modality;
      Cstring manufacturer;
      Cstring model;
      Cstring institution;
      Cstring station_id;
      Cstring ref_physician;
      Cstring procedure;
      Cstring study_id;
      Cstring acquisition_id;
   } study;
   struct {
      Cstring scan_seq;
      double rep_time;
      double echo_time;
      double inv_time;
      double num_avg;
      double imaging_freq;
      Cstring imaged_nucl;
   } acq;
   Acr_Group group_list;
} General_Info;

/* Structure for file-specific info */
typedef struct {
   int valid;
   int bits_alloc;
   int bits_stored;
   double pixel_max;
   double pixel_min;
   double slice_max;
   double slice_min;
   double slice_position;
   double dyn_begin_time;
   int index[MRI_NDIMS];
} File_Info;

/* Structure for image data */
typedef struct {
   int free;
   int nrows;
   int ncolumns;
   unsigned short *data;
} Image_Data;

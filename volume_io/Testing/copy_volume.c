#include  <def_mni.h>

int  main(
    int   argc,
    char  *argv[] )
{
    Status         status;
    int            sizes[MAX_DIMENSIONS];
    Real           separations[MAX_DIMENSIONS];
    Real           min_value, max_value, fraction_done;
    Volume         volume;
    char           *input_filename, *output_filename, *dummy;
    char           *tmp;
    Minc_file      file;
    static String  dim_names[3] = { MIzspace, MIyspace, MIxspace };
    Real           start_time, end_time;

    initialize_argument_processing( argc, argv );

    if( !get_string_argument( "", &input_filename ) ||
        !get_string_argument( "", &output_filename ) )
    {
        print( "Need source and destination filename.\n" );
    }

    if( get_string_argument( "", &dummy ) )
    {
        (void) strcpy( dim_names[0], MIxspace );
        (void) strcpy( dim_names[1], MIyspace );
        (void) strcpy( dim_names[2], MIzspace );
    }

    print( "Inputting volume: %s\n", input_filename );
    volume = create_volume( 3, dim_names, NC_UNSPECIFIED, FALSE, 0.0, 0.0 );

    start_time = current_realtime_seconds();

    file = initialize_minc_input( input_filename, volume );

    while( input_more_minc_file( file, &fraction_done ) )
    {
    }

    end_time = current_realtime_seconds();

    print( "Seconds: %g\n", end_time - start_time );

    return( 0 );

    get_volume_sizes( volume, sizes );
    get_volume_separations( volume, separations );
    get_volume_range( volume, &min_value, &max_value );

    print( "Volume %s: %d by %d by %d\n",
            input_filename, sizes[X], sizes[Y], sizes[Z] );
    print( "Thickness: %g %g %g\n",
            separations[X], separations[Y], separations[Z] );
    print( "%g %g\n", min_value, max_value );

    file = initialize_minc_output( output_filename, 3, dim_names, sizes,
                                   NC_BYTE, FALSE, min_value, max_value,
                                   &volume->voxel_to_world_transform );

    status = output_minc_volume( file, volume );

    status = close_minc_output( file );

    return( status != OK );
}
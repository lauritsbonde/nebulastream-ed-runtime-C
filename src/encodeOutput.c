#include <stdlib.h>
#include <stdio.h>

#include "pb_encode.h"
#include "pb_decode.h"
#include "EndDeviceProtocol.pb.h"
#include "common.h"
#include "operators.h"


bool QueryResponse_callback(pb_istream_t *istream, pb_ostream_t *ostream, const pb_field_iter_t *field) {
    PB_UNUSED(istream);
    if (ostream != NULL && field->tag == EndDeviceProtocol_Output_responses_tag)
    {
        DIR *dir = *(DIR**)field->pData;
        struct dirent *file;
        FileInfo fileinfo = {};

        while ((file = readdir(dir)) != NULL)
        {
            fileinfo.inode = file->d_ino;
            strncpy(fileinfo.name, file->d_name, sizeof(fileinfo.name));
            fileinfo.name[sizeof(fileinfo.name) - 1] = '\0';

            /* This encodes the header for the field, based on the constant info
            * from pb_field_t. */
            if (!pb_encode_tag_for_field(ostream, field))
                return false;

            /* This encodes the data for the field, based on our FileInfo structure. */
            if (!pb_encode_submessage(ostream, FileInfo_fields, &fileinfo))
                return false;
        }

        /* Because the main program uses pb_encode_delimited(), this callback will be
        * called twice. Rewind the directory for the next call. */
        rewinddir(dir);
    }

    return true;
}
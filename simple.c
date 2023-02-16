/**
 * @file simple.c
 * @brief Hello World for NanoPB
 *
 * This is based on nanopb's simple example, with some more fields in the proto
 * file, more output, generation via protoc and ufw/makemehappy based build.
 */

#include <stdio.h>
#include <stdlib.h>

#include <inttypes.h>

#include <pb_encode.h>
#include <pb_decode.h>

#include <ufw/compiler.h>

#include "simple.pb.h"

int
main(UNUSED int argc, UNUSED char *argv[])
{
    uint8_t buffer[128];
    size_t message_length;
    bool status;

    printf("Sending a message...\n");
    {
        /* Transmit */
        SimpleMessage message = SimpleMessage_init_zero;
        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
        message.number = -63;
        message.unsigned_number = 0x1234567890abcdefULL;
        message.floating_number = 123.42e-69;
        status = pb_encode(&stream, SimpleMessage_fields, &message);
        message_length = stream.bytes_written;
        if (status == false) {
            printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
            return EXIT_FAILURE;
        }
    }

    /* Hexdump the wire. */
    printf("Data on the wire...\n");
    for (size_t i = 0u; i < message_length; ++i) {
        printf(" %02x", buffer[i]);
    }
    printf("\n");

    printf("Receiving a message...\n");
    {
        /* Receive */
        SimpleMessage message = SimpleMessage_init_zero;
        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);
        status = pb_decode(&stream, SimpleMessage_fields, &message);
        if (status == false) {
            printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
            return EXIT_FAILURE;
        }
        printf("Your signed number was %"PRId32"!\n", message.number);
        printf("Your unsigned number was 0x%"PRIx64"!\n", message.unsigned_number);
        printf("Your floating number was %e!\n", message.floating_number);
    }
    return EXIT_SUCCESS;
}

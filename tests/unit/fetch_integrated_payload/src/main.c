/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <unity.h>
#include <stdint.h>
#include "suit.h"
#include "suit_platform/cmock_suit_platform.h"
#include "suit_platform_mock_ext.h"

#define ASSIGNED_COMPONENT_HANDLE 0x1E054000


static uint8_t manifest_buf[] = {
	0xD8, 0x6B, 0xA4, 0x02, 0x58, 0x73, 0x82, 0x58,
	0x24, 0x82, 0x2F, 0x58, 0x20, 0x83, 0xDA, 0xB4,
	0xC8, 0x99, 0x8D, 0x42, 0xBE, 0xF9, 0x9D, 0x36,
	0x83, 0xB1, 0x88, 0x20, 0x34, 0x98, 0x97, 0xAD,
	0xAC, 0xB6, 0xBC, 0x8A, 0x9A, 0x62, 0xBC, 0x8F,
	0xB1, 0xC7, 0x11, 0x17, 0xB6, 0x58, 0x4A, 0xD2,
	0x84, 0x43, 0xA1, 0x01, 0x26, 0xA0, 0xF6, 0x58,
	0x40, 0x0A, 0xC7, 0x7A, 0x88, 0xA2, 0x9E, 0x45,
	0x5D, 0x6A, 0x9D, 0x6E, 0xC9, 0x04, 0x77, 0x24,
	0x8B, 0x8E, 0x5E, 0x2F, 0xFE, 0x9C, 0xF0, 0x22,
	0x4F, 0xB7, 0x7A, 0x3C, 0x36, 0xA0, 0xF0, 0x79,
	0xBB, 0x2B, 0x78, 0xB2, 0xEA, 0xEB, 0x20, 0x00,
	0x2B, 0x19, 0x3B, 0xE9, 0xA1, 0x3E, 0xFB, 0x83,
	0xF6, 0xA8, 0x7A, 0x03, 0x74, 0x2D, 0xF1, 0x08,
	0x4E, 0x5B, 0xD0, 0x4D, 0x45, 0xF9, 0x97, 0x39,
	0xC0, 0x03, 0x58, 0xAE, 0xA7, 0x01, 0x01, 0x02,
	0x01, 0x03, 0x58, 0x64, 0xA2, 0x02, 0x81, 0x82,
	0x41, 0x58, 0x44, 0x1E, 0x05, 0x40, 0x00, 0x04,
	0x58, 0x56, 0x86, 0x14, 0xA4, 0x01, 0x50, 0x2B,
	0xDC, 0x1C, 0x07, 0xE0, 0xD1, 0x54, 0x84, 0xBE,
	0x50, 0x63, 0x17, 0x4D, 0x5A, 0x74, 0xC3, 0x02,
	0x50, 0x85, 0x20, 0xEA, 0x9C, 0x51, 0x5E, 0x57,
	0x79, 0x8B, 0x5F, 0xBD, 0xAD, 0x67, 0xDE, 0xC7,
	0xD9, 0x03, 0x58, 0x24, 0x82, 0x2F, 0x58, 0x20,
	0x5F, 0xC3, 0x54, 0xBF, 0x8E, 0x8C, 0x50, 0xFB,
	0x4F, 0xBC, 0x2C, 0xFA, 0xEB, 0x04, 0x53, 0x41,
	0xC9, 0x80, 0x6D, 0xEA, 0xBD, 0xCB, 0x41, 0x54,
	0xFB, 0x79, 0xCC, 0xA4, 0xF0, 0xC9, 0x8C, 0x12,
	0x0E, 0x19, 0x01, 0x00, 0x01, 0x0F, 0x02, 0x0F,
	0x07, 0x43, 0x82, 0x03, 0x0F, 0x09, 0x43, 0x82,
	0x17, 0x02, 0x11, 0x51, 0x86, 0x14, 0xA1, 0x15,
	0x68, 0x23, 0x61, 0x70, 0x70, 0x2E, 0x62, 0x69,
	0x6E, 0x15, 0x02, 0x03, 0x0F, 0x17, 0x82, 0x2F,
	0x58, 0x20, 0xAE, 0xFA, 0x77, 0xB3, 0xAC, 0x67,
	0x01, 0xAA, 0x9A, 0xAE, 0x7A, 0xC2, 0x0C, 0x70,
	0x14, 0x42, 0xBE, 0xAC, 0x88, 0xD1, 0xBC, 0xFA,
	0x39, 0xDD, 0x8F, 0x65, 0x24, 0x37, 0x4E, 0x92,
	0xB6, 0xF0, 0x17, 0x58, 0x89, 0xA1, 0x82, 0x41,
	0x58, 0x44, 0x1E, 0x05, 0x40, 0x00, 0xA6, 0x01,
	0x78, 0x18, 0x4E, 0x6F, 0x72, 0x64, 0x69, 0x63,
	0x20, 0x53, 0x65, 0x6D, 0x69, 0x63, 0x6F, 0x6E,
	0x64, 0x75, 0x63, 0x74, 0x6F, 0x72, 0x20, 0x41,
	0x53, 0x41, 0x02, 0x6E, 0x6E, 0x52, 0x46, 0x35,
	0x34, 0x32, 0x30, 0x5F, 0x63, 0x70, 0x75, 0x61,
	0x70, 0x70, 0x03, 0x6D, 0x6E, 0x6F, 0x72, 0x64,
	0x69, 0x63, 0x73, 0x65, 0x6D, 0x69, 0x2E, 0x6E,
	0x6F, 0x04, 0x78, 0x1D, 0x54, 0x68, 0x65, 0x20,
	0x6E, 0x52, 0x46, 0x35, 0x33, 0x38, 0x34, 0x30,
	0x20, 0x61, 0x70, 0x70, 0x6C, 0x69, 0x63, 0x61,
	0x74, 0x69, 0x6F, 0x6E, 0x20, 0x63, 0x6F, 0x72,
	0x65, 0x05, 0x78, 0x1A, 0x53, 0x61, 0x6D, 0x70,
	0x6C, 0x65, 0x20, 0x61, 0x70, 0x70, 0x6C, 0x69,
	0x63, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x63,
	0x6F, 0x72, 0x65, 0x20, 0x46, 0x57, 0x06, 0x66,
	0x76, 0x31, 0x2E, 0x30, 0x2E, 0x30, 0x68, 0x23,
	0x61, 0x70, 0x70, 0x2E, 0x62, 0x69, 0x6E, 0x59,
	0x01, 0x00, 0xC7, 0x9C, 0xAB, 0x9D, 0xE8, 0x33,
	0x7F, 0x30, 0x14, 0xEB, 0xAC, 0x02, 0xAF, 0x26,
	0x01, 0x5E, 0x80, 0x6D, 0x88, 0xA1, 0xDB, 0x11,
	0xA7, 0x31, 0xDF, 0xA6, 0xEC, 0xCB, 0x9B, 0x48,
	0x0D, 0xC8, 0x34, 0x40, 0x6D, 0x30, 0x86, 0x7D,
	0xE8, 0x1B, 0xEC, 0x3C, 0xF5, 0x40, 0xD0, 0x48,
	0x18, 0x82, 0x11, 0x9D, 0x7C, 0x3F, 0x6C, 0xE5,
	0x8F, 0xF1, 0xD3, 0x5D, 0xE1, 0x51, 0xF7, 0x6A,
	0x0F, 0xAF, 0x0B, 0xBD, 0x4C, 0x5F, 0xA5, 0x34,
	0x1A, 0x66, 0xDB, 0x22, 0xEC, 0x63, 0xED, 0x4B,
	0xAB, 0xC7, 0xC8, 0xF7, 0x59, 0xD8, 0xD6, 0x9E,
	0xEC, 0x71, 0x1B, 0x24, 0x20, 0xB9, 0xAE, 0xE1,
	0x3B, 0xFC, 0xAE, 0xB8, 0x77, 0xAC, 0xA4, 0x57,
	0x34, 0x97, 0x84, 0x4F, 0x58, 0xD5, 0x68, 0x08,
	0x6F, 0xE3, 0x9C, 0x7E, 0x1B, 0xD7, 0x38, 0x22,
	0x98, 0x48, 0xF8, 0x7A, 0x67, 0xB2, 0xD9, 0xAC,
	0xC5, 0x34, 0xC1, 0x27, 0x82, 0x8E, 0x42, 0x79,
	0x84, 0x21, 0x37, 0x4C, 0x41, 0x4A, 0x0F, 0xE2,
	0x7F, 0xA0, 0x6A, 0x19, 0x13, 0x3D, 0x52, 0x22,
	0x7F, 0xD6, 0x2F, 0x71, 0x12, 0x76, 0xAB, 0x25,
	0x9C, 0xFC, 0x67, 0x08, 0x03, 0x7C, 0xDB, 0x18,
	0xE6, 0x45, 0xF8, 0x99, 0xC2, 0x9E, 0x2C, 0xE3,
	0x9B, 0x25, 0xA9, 0x7B, 0x09, 0xFF, 0x00, 0x57,
	0x26, 0x08, 0x0A, 0x11, 0x42, 0xCF, 0x82, 0xA2,
	0x6B, 0x2A, 0x99, 0xF9, 0x71, 0x9D, 0x14, 0x19,
	0x5C, 0x5C, 0x78, 0x31, 0x60, 0x42, 0x4A, 0x18,
	0x1F, 0xEC, 0x78, 0x6A, 0x9A, 0x7C, 0x4F, 0xCF,
	0xE8, 0x5A, 0x29, 0x65, 0xCD, 0x01, 0x3B, 0x6D,
	0x53, 0xBB, 0xC6, 0xDB, 0xDA, 0xD5, 0x8F, 0xF7,
	0xF4, 0xD9, 0xB9, 0x0A, 0x03, 0x4B, 0xFF, 0x33,
	0xAB, 0x3B, 0xC5, 0xAF, 0xD0, 0xB8, 0x2C, 0x0F,
	0x6A, 0xA9, 0x11, 0xB0, 0xE8, 0x57, 0x8C, 0x92,
	0x53, 0x81
};
static const size_t manifest_len = sizeof(manifest_buf);
static struct suit_processor_state state;


static uint8_t vid_uuid[] = {
	0x2B, 0xDC, 0x1C, 0x07, 0xE0, 0xD1, 0x54, 0x84,
	0xBE, 0x50, 0x63, 0x17, 0x4D, 0x5A, 0x74, 0xC3,
};
struct zcbor_string exp_vid_uuid = {
	.value = vid_uuid,
	.len = sizeof(vid_uuid),
};

static uint8_t cid_uuid[] = {
	0x85, 0x20, 0xEA, 0x9C, 0x51, 0x5E, 0x57, 0x79,
	0x8B, 0x5F, 0xBD, 0xAD, 0x67, 0xDE, 0xC7, 0xD9,
};
struct zcbor_string exp_cid_uuid = {
	.value = cid_uuid,
	.len = sizeof(cid_uuid),
};

static uint8_t image_digest[] = {
	0x5F, 0xC3, 0x54, 0xBF, 0x8E, 0x8C, 0x50, 0xFB,
	0x4F, 0xBC, 0x2C, 0xFA, 0xEB, 0x04, 0x53, 0x41,
	0xC9, 0x80, 0x6D, 0xEA, 0xBD, 0xCB, 0x41, 0x54,
	0xFB, 0x79, 0xCC, 0xA4, 0xF0, 0xC9, 0x8C, 0x12,
};
struct zcbor_string exp_image_digest = {
	.value = image_digest,
	.len = sizeof(image_digest),
};
struct zcbor_string exp_image_payload = {
	.value = &manifest_buf[450],
	.len = 256,
};

static uint8_t text_digest[] = {
	0xAE, 0xFA, 0x77, 0xB3, 0xAC, 0x67, 0x01, 0xAA,
	0x9A, 0xAE, 0x7A, 0xC2, 0x0C, 0x70, 0x14, 0x42,
	0xBE, 0xAC, 0x88, 0xD1, 0xBC, 0xFA, 0x39, 0xDD,
	0x8F, 0x65, 0x24, 0x37, 0x4E, 0x92, 0xB6, 0xF0,
};
struct zcbor_string exp_text_digest = {
	.value = text_digest,
	.len = sizeof(text_digest),
};
struct zcbor_string exp_text_payload = {
	.value = &(manifest_buf[301]),
	.len = 137,
};

static uint8_t manifest_digest[] = {
	0x83, 0xda, 0xb4, 0xc8, 0x99, 0x8d, 0x42, 0xbe,
	0xf9, 0x9d, 0x36, 0x83, 0xb1, 0x88, 0x20, 0x34,
	0x98, 0x97, 0xad, 0xac, 0xb6, 0xbc, 0x8a, 0x9a,
	0x62, 0xbc, 0x8f, 0xb1, 0xc7, 0x11, 0x17, 0xb6,
};
struct zcbor_string exp_manifest_digest = {
	.value = manifest_digest,
	.len = sizeof(manifest_digest),
};
struct zcbor_string exp_manifest_payload = {
	.value = &(manifest_buf[122]),
	.len = 176,
};


void test_suit_decode_envelope(void)
{
	/* The envelope decoding is fully handled by the ZCBOR code and does not call platform APIs */
	int err = suit_decode_envelope(manifest_buf, manifest_len, &state);
	TEST_ASSERT_EQUAL(SUIT_SUCCESS, err);
}

void test_suit_validate_envelope(void)
{
	int err = 0;

	struct zcbor_string exp_signature = {
		.value = &(manifest_buf[57]),
		.len = 64,
	};
	uint8_t signature1_cbor[] = {
		0x84, // Sig_structure1: array(4)
			0x6A, // context: text(10)
				'S', 'i', 'g', 'n', 'a', 't', 'u', 'r', 'e', '1',
			0x43, // body_protected: bytes(3)
				0xA1, // header_map: map(1)
					0x01, // alg_id: 1
						0x26, // ES256: -7
			0x40, // external_aad: bytes(0)
			0x58, // payload: bytes(36)
				0x24, 0x82, 0x2F, 0x58, 0x20,
				0x83, 0xda, 0xb4, 0xc8, 0x99, 0x8d, 0x42, 0xbe,
				0xf9, 0x9d, 0x36, 0x83, 0xb1, 0x88, 0x20, 0x34,
				0x98, 0x97, 0xad, 0xac, 0xb6, 0xbc, 0x8a, 0x9a,
				0x62, 0xbc, 0x8f, 0xb1, 0xc7, 0x11, 0x17, 0xb6,
	};
	struct zcbor_string exp_data = {
		.value = signature1_cbor,
		.len = sizeof(signature1_cbor),
	};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&(signature1_cbor[23]), manifest_digest, sizeof(manifest_digest), "Please fix the test: manifest digest inside signature structure is incorrect");

	/* The envelope validation should:
	 * - Verify the manifest signature
	 * - Verify that the manifest digest matches with the manifest contents
	 */
	__cmock_suit_plat_authenticate_ExpectComplexArgsAndReturn(suit_cose_es256, NULL, &exp_signature, &exp_data, SUIT_SUCCESS);
	__cmock_suit_plat_check_digest_ExpectComplexArgsAndReturn(suit_cose_sha256, &exp_manifest_digest, &exp_manifest_payload, SUIT_SUCCESS);

	err = suit_validate_envelope(&state);
	TEST_ASSERT_EQUAL(SUIT_SUCCESS, err);
}

void test_suit_decode_manifest(void)
{
	/* The manifest decoding is fully handled by the ZCBOR code and does not call platform APIs */
	int err = suit_decode_manifest(&state);
	TEST_ASSERT_EQUAL(SUIT_SUCCESS, err);
}

void test_suit_validate_manifest(void)
{
	suit_component_t component_handle = ASSIGNED_COMPONENT_HANDLE;
	uint8_t app_id[] = {
		0x82, // SUIT_Component_Identifier: array(2)
			0x41, // bstr: bytes(1)
				'X',
			0x44, // bstr: bytes(4)
				0x1E, 0x05, 0x40, 0x00,
	};
	struct zcbor_string exp_component_id = {
		.value = app_id,
		.len = sizeof(app_id),
	};

	/* The manifest validation should:
	 * - Verify the manifest sequence number
	 * - Obtain a platform-specific component handle for each component described by the manifest
	 * - Verify digest of the severed text field
	 * - Execute dry-run commands for each command sequence present in the manifest
	 *   - Check FETCH (integrated) command from the install step
	 *   - Check INVOKE command from the invoke step
	 */
	__cmock_suit_plat_check_sequence_num_ExpectAndReturn(1, SUIT_SUCCESS);
	__cmock_suit_plat_create_component_handle_ExpectComplexArgsAndReturn(&exp_component_id, state.key_ids, 0, NULL, SUIT_SUCCESS);
	__cmock_suit_plat_create_component_handle_IgnoreArg_component_handle();
	__cmock_suit_plat_create_component_handle_ReturnThruPtr_component_handle(&component_handle);

	__cmock_suit_plat_check_digest_ExpectComplexArgsAndReturn(suit_cose_sha256, &exp_text_digest, &exp_text_payload, SUIT_SUCCESS);
	__cmock_suit_plat_check_fetch_integrated_ExpectComplexArgsAndReturn(ASSIGNED_COMPONENT_HANDLE, &exp_image_payload, SUIT_SUCCESS);
	__cmock_suit_plat_check_invoke_ExpectAndReturn(ASSIGNED_COMPONENT_HANDLE, NULL, SUIT_SUCCESS);

	int err = suit_validate_manifest(&state);
	TEST_ASSERT_EQUAL(SUIT_SUCCESS, err);
}

void test_suit_process_step_no_step(void)
{
	/* SUIT_NO_STEP is not a valid step - it serves as a boundary value of the enum. */
	int err = suit_process_manifest(&state, SUIT_NO_STEP);
	TEST_ASSERT_EQUAL(SUIT_ERR_UNAVAILABLE_COMMAND_SEQ, err);
}

void test_suit_process_step_payload_fetch(void)
{
	/* SUIT_PAYLOAD_FETCH command sequence is not present in the sample manifest.
	 * The internal payload is fetched to the executable slot by executing FETCH command
	 * from the INSTALL step.
	 */
	int err = suit_process_manifest(&state, SUIT_PAYLOAD_FETCH);
	TEST_ASSERT_EQUAL(SUIT_ERR_UNAVAILABLE_COMMAND_SEQ, err);
}

void test_suit_process_step_install(void)
{
	/* SUIT_INSTALL should:
	 * - execute the shared sequence (VID and CID checks),
	 * - copy the integrated payload into executable slot through FETCH (integrated) command
	 * - verify the image digest in the executable slot
	 */
	__cmock_suit_plat_check_vid_ExpectComplexArgsAndReturn(&exp_vid_uuid, ASSIGNED_COMPONENT_HANDLE, SUIT_SUCCESS);
	__cmock_suit_plat_check_cid_ExpectComplexArgsAndReturn(&exp_cid_uuid, ASSIGNED_COMPONENT_HANDLE, SUIT_SUCCESS);
	__cmock_suit_plat_fetch_integrated_ExpectComplexArgsAndReturn(ASSIGNED_COMPONENT_HANDLE, &exp_image_payload, SUIT_SUCCESS);
	__cmock_suit_plat_check_image_match_ExpectComplexArgsAndReturn(suit_cose_sha256, &exp_image_digest, 256, ASSIGNED_COMPONENT_HANDLE, SUIT_SUCCESS);

	int err = suit_process_manifest(&state, SUIT_INSTALL);
	TEST_ASSERT_EQUAL(SUIT_SUCCESS, err);
}

void test_suit_process_step_validate(void)
{
	/* SUIT_VALIDATE should:
	 * - execute the shared sequence (VID and CID checks)
	 * - verify the image digest in the executable slot.
	 */
	__cmock_suit_plat_check_vid_ExpectComplexArgsAndReturn(&exp_vid_uuid, ASSIGNED_COMPONENT_HANDLE, SUIT_SUCCESS);
	__cmock_suit_plat_check_cid_ExpectComplexArgsAndReturn(&exp_cid_uuid, ASSIGNED_COMPONENT_HANDLE, SUIT_SUCCESS);
	__cmock_suit_plat_check_image_match_ExpectComplexArgsAndReturn(suit_cose_sha256, &exp_image_digest, 256, ASSIGNED_COMPONENT_HANDLE, SUIT_SUCCESS);

	int err = suit_process_manifest(&state, SUIT_VALIDATE);
	TEST_ASSERT_EQUAL(SUIT_SUCCESS, err);
}

void test_suit_process_step_load(void)
{
	/* SUIT_LOAD command sequence is not present in the sample manifest. */
	int err = suit_process_manifest(&state, SUIT_LOAD);
	TEST_ASSERT_EQUAL(SUIT_ERR_UNAVAILABLE_COMMAND_SEQ, err);
}

void test_suit_process_step_invoke(void)
{
	/* SUIT_INVOKE should:
	 * - execute the shared sequence (VID and CID checks)
	 * - execute the INVOKE command.
	 * The image validity is expected to be checked in the SUIT_VALIDATE step.
	 */
	__cmock_suit_plat_check_vid_ExpectComplexArgsAndReturn(&exp_vid_uuid, ASSIGNED_COMPONENT_HANDLE, SUIT_SUCCESS);
	__cmock_suit_plat_check_cid_ExpectComplexArgsAndReturn(&exp_cid_uuid, ASSIGNED_COMPONENT_HANDLE, SUIT_SUCCESS);
	__cmock_suit_plat_invoke_ExpectAndReturn(ASSIGNED_COMPONENT_HANDLE, NULL, SUIT_SUCCESS);

	int err = suit_process_manifest(&state, SUIT_INVOKE);
	TEST_ASSERT_EQUAL(SUIT_SUCCESS, err);
}

void test_suit_process_step_last_step(void)
{
	/* SUIT_LAST_STEP is not a valid step - it serves as a boundary value of the enum. */
	int err = suit_process_manifest(&state, SUIT_LAST_STEP);
	TEST_ASSERT_EQUAL(SUIT_ERR_UNAVAILABLE_COMMAND_SEQ, err);
}


/* It is required to be added to each test. That is because unity is using
 * different main signature (returns int) and zephyr expects main which does
 * not return value.
 */
extern int unity_main(void);

void main(void)
{
	(void)unity_main();
}

/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <stdint.h>
#include <zcbor_decode.h>
#include <zcbor_common.h>
#include <manifest_types.h>
#include <manifest_decode.h>
#include <suit_types.h>
#include <suit_condition.h>
#include <suit_directive.h>



typedef union {
	struct SUIT_Condition_ condition;
	struct SUIT_Directive_ directive;
} suit_command_t;

int suit_validate_common_sequence(struct suit_processor_state *state, struct zcbor_string *cmd_seq_str)
{

}


int suit_validate_command_sequence(struct suit_processor_state *state, struct zcbor_string *cmd_seq_str)
{
	state->dry_run = suit_bool_true;
}


int suit_run_command_sequence(struct suit_processor_state *state, struct zcbor_string *cmd_seq_str)
{
	size_t decoded_len;
	suit_command_t result;
	ZCBOR_STATE_D(d_state, 1, cmd_seq_str.value, cmd_seq_str.len, 1);

	int ret = zcbor_list_start_decode(d_state);

	if (ret != ZCBOR_SUCCESS) {
		return ZCBOR_ERR_TO_SUIT_ERR(ret);
	}
	if (d_state->indefinite_length_array) {
		return SUIT_ERR_DECODING;
	}

	for (int i = 0; i < d_state->elem_count, i++) {
		if (ret = cbor_decode_SUIT_Condition(
			d_state->payload, d_state->payload_end - d_state->payload,
			&result.condition, &decoded_len) == ZCBOR_SUCCESS) {
			int retval;

			if (i == 0) {
				/* Each sequence should begin with a set-component-index command.*/
				return SUIT_ERR_MANIFEST_VALIDATION;
			}

			for (int j = 0; j < state->num_components; j++) {
				if (state->current_components[j]) {
					switch (result.condition._SUIT_Condition_choice) {
					case _SUIT_Condition___suit_condition_vendor_identifier:
						retval = suit_condition_vendor_identifier(state, &state->components[j]);
						break;
					case _SUIT_Condition___suit_condition_class_identifier:
						retval = suit_condition_class_identifier(state, &state->components[j]);
						break;
					case _SUIT_Condition___suit_condition_device_identifier:
						retval = suit_condition_device_identifier(state, &state->components[j]);
						break;
					case _SUIT_Condition___suit_condition_image_match:
						retval = suit_condition_image_match(state, &state->components[j]);
						break;
					case _SUIT_Condition___suit_condition_component_slot:
						retval = suit_condition_component_slot(state, &state->components[j]);
						break;
					case _SUIT_Condition___suit_condition_abort:
						retval = suit_condition_abort(state, &state->components[j]);
						break;
					default:
						retval = SUIT_ERR_DECODING;
						break;
					}
					if ((retval != SUIT_SUCCESS)
						&& !((retval == SUIT_FAIL_CONDITION)
							&& (state->soft_failure == suit_bool_true))) {
						return retval;
					}
				}
			}
			d_state->payload += decoded_len;
			continue;
		}

		if (ret = cbor_decode_SUIT_Directive(
			d_state->payload, d_state->payload_end - d_state->payload,
			&result.directive, &decoded_len) == ZCBOR_SUCCESS) {
			int retval;

			if (i == 0) {
				if (result.directive._SUIT_Directive_choice
					!= _SUIT_Directive___suit_directive_set_component_index) {
					/* Each sequence should begin with a set-component-identifier command.*/
					return SUIT_ERR_MANIFEST_VALIDATION;
				}
			}

			switch (result.directive._SUIT_Directive_choice) {
			case _SUIT_Directive___suit_directive_set_component_index:
				retval = set_current_components(state,
					&result.directive._SUIT_Directive___suit_directive_set_component_index__IndexArg);
				break;
			case _SUIT_Directive___suit_directive_try_each:
				retval = suit_directive_try_each(state, &result.directive._SUIT_Directive___suit_directive_try_each__SUIT_Directive_Try_Each_Argument);
				break;
			case _SUIT_Directive___suit_directive_override_parameters:
				retval = suit_directive_override_parameters(state,
					result.directive.___suit_directive_override_parameters_map__SUIT_Parameters,
					result.directive.___suit_directive_override_parameters_map__SUIT_Parameters_count);
				break;
			case _SUIT_Directive___suit_directive_fetch:
				retval = suit_directive_fetch(state);
				break;
			case _SUIT_Directive___suit_directive_copy:
				retval = suit_directive_copy(state);
				break;
			case _SUIT_Directive___suit_directive_run:
				retval = suit_directive_run(state);
				break;
			default:
				retval = SUIT_ERR_DECODING;
				break;
			}
			if (retval != SUIT_SUCCESS) {
				return retval;
			}
			d_state->payload += decoded_len;
			continue;
		}

		/* Should not come here. */
		return SUIT_ERR_DECODING;
	}

	if (d_state->payload == d_state->payload_end) {
		return SUIT_SUCCESS;
	}

	return SUIT_ERR_DECODING;
}

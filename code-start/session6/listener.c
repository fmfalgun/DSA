/*
 * script to list the bluetooth connected/disconnected devices
 */

#include <dbus/dbus.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "bt_struct.h"

struct BT_NODE devices[32];
int devices_count = 0;
char current_object_path[64];
char current_interface[64];
char current_property[64];

void walker (DBusMessageIter iter, int level){	
	int type;
	do{
		type = dbus_message_iter_get_arg_type(&iter);
		DBusBasicValue val;
		if (type == 97 || type == 101 || type == 118 || type == 114){
			DBusMessageIter sub;
			dbus_message_iter_recurse(&iter, &sub);
			walker(sub, level+1);
		}
		
		else if(type == 0) continue;
		else {
			dbus_message_iter_get_basic(&iter, &val);
		
			// initial checks (optional)
			/*
			if (type == 98) printf("type = %i, value = %d, level = %i\n",type, val.bool_val, level);		
			if (type == 110) printf("type = %i, value = %d, level = %i\n",type, val.i16, level);		
			if (type == 111 || type == 115) printf("type = %i, value = %s, level = %i\n",type, val.str, level);				     
			if (type == 113) printf("type = %i, value = %u, level = %i\n",type, val.u16, level);		
			if (type == 117) printf("type = %i, value = %u, level = %i\n",type, val.u32, level);		
			if (type == 121) printf("type = %i, value = %u, level = %i\n",type, val.byt, level);	
			*/

			// extracting status and putting in global variable to have proper record
			struct BT_NODE *temp;
			
			if (level == 4 && (type == 115 || type == 111)) {
				strncpy(current_interface, val.str, sizeof(current_interface));
				if (strcmp(val.str, "org.bluez.Bearer.BREDR1") == 0 && devices_count > 0)
    					strncpy(devices[devices_count - 1].protocol, "BR/EDR", sizeof(devices[devices_count - 1].protocol));
				// printf("current_interface = %s\n", current_interface);
			}
			else if (level == 6 && (type == 115 || type == 111)) strncpy(current_property, val.str, sizeof(current_property));
			else if ((level == 7) && (strcmp(current_interface, "org.bluez.Device1") == 0)) {
				temp = &devices[devices_count - 1];
				if (strcmp(current_property, "Address") == 0) 		strncpy(temp->address, val.str, sizeof(temp->address)) ;
				if (strcmp(current_property, "AddressType") == 0) 	strncpy(temp->address_type, val.str, sizeof(temp->address_type)) ;
				if (strcmp(current_property, "Name") == 0) 		strncpy(temp->name, val.str, sizeof(temp->name)) ;
				if (strcmp(current_property, "Alias") == 0) 		strncpy(temp->alias, val.str, sizeof(temp->alias)) ;
				if (strcmp(current_property, "Class") == 0) 		temp->bt_class = val.u32 ;
				if (strcmp(current_property, "Icon") == 0) 		strncpy(temp->icon, val.str, sizeof(temp->icon)) ;
				if (strcmp(current_property, "Paired") == 0) 		temp->paired = val.bool_val ;
				if (strcmp(current_property, "Bonded") == 0) 		temp->bonded = val.bool_val ;
				if (strcmp(current_property, "Trusted") == 0) 		temp->trusted = val.bool_val ;
				if (strcmp(current_property, "Blocked") == 0)		temp->blocked = val.bool_val ;
				if (strcmp(current_property, "LegacyPairing") == 0) 	temp->legacy_pairing = val.bool_val ;
				if (strcmp(current_property, "CablePairing") == 0)	temp->cable_pairing 	= val.bool_val ;
				if (strcmp(current_property, "Connected") == 0)		temp->connected = val.bool_val ;
				if (strcmp(current_property, "ServicesResolved") == 0) 	temp->services_resolved = val.bool_val ;
				if (strcmp(current_property, "Adapter") == 0) 		strncpy(temp->adapter, val.str, sizeof(temp->adapter)) ;
				if (strcmp(current_property, "RSSI") == 0) 		temp->rssi = val.i16 ;
				if (strcmp(current_property, "Protocol") == 0) 		strncpy(temp->protocol, val.str, sizeof(temp->protocol)) ;
			}
			else if (level == 8 && strcmp(current_interface, "org.bluez.Device1") == 0) {
				if (strcmp(current_property, "UUIDs") == 0){
					strncpy(devices[devices_count - 1].uuids[devices[devices_count - 1].
							uuid_count],val.str, sizeof(devices[devices_count - 1].
								uuids[devices[devices_count - 1].uuid_count]));
					devices[devices_count - 1].uuid_count++;
				}
			}
			else if((level == 2) && (type == 111) && (strstr(val.str, "dev_") != NULL)){
				devices_count ++;
			}
		}
		dbus_message_iter_next(&iter);
	}while (type != DBUS_TYPE_INVALID);
}

void main (void){
	DBusError err;
	dbus_error_init(&err);
	DBusConnection *conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
	DBusMessage *msg = dbus_message_new_method_call(
		"org.bluez",
		"/",
		"org.freedesktop.DBus.ObjectManager",
		"GetManagedObjects"		
	);
	DBusMessage *reply = dbus_connection_send_with_reply_and_block(
		conn, msg, -1, &err		
	);
	
	if (dbus_error_is_set(&err)){
		printf("Error: %s\n", err.name);
		printf("Details: %s\n", err.message);
	}
	else printf("got reply\n");
	
	DBusMessageIter iter;
	
	dbus_message_iter_init(reply, &iter);
	/*
	while (dbus_message_iter_get_arg_type(&iter) 
		!= DBUS_TYPE_INVALID){
		int type = dbus_message_iter_get_arg_type(&iter);
		printf("type = %i\n",type);	
		dbus_message_iter_next(&iter);
	}
	*/
	walker(iter, 0);
	
	//printing all values in devices
	printf("devices count = %i\n", devices_count);
	for (int i = 0; i < devices_count; i++){
		printf("Device %i\n", i);
		printf("	address: %s\n", 	  devices[i].address);
		printf("	address type: %s\n", 	  devices[i].address_type);
		printf("	name: %s\n", 		  devices[i].name);
		printf("	alias: %s\n", 		  devices[i].alias);
		printf("	bt_class: %i\n", 	  devices[i].bt_class);
		printf("	icon: %s\n", 		  devices[i].icon);
		printf("	paired: %i\n", 		  devices[i].paired);
		printf("	bonded: %i\n", 		  devices[i].bonded);
		printf("	trusted: %i\n", 	  devices[i].trusted);
		printf("	blocked: %i\n", 	  devices[i].blocked);
		printf("	legacy pairing: %i\n", 	  devices[i].legacy_pairing);
		printf("	connected: %i\n", 	  devices[i].connected);
		printf("	services resolved: %i\n", devices[i].services_resolved);
		printf("	uuid count: %i\n", 	  devices[i].uuid_count);
		for(int j = 0; j < devices[i].uuid_count; j++)
		printf("		uuids: %s\n", 		  devices[i].uuids[j]);
		printf("	adapter: %s\n", 	  devices[i].adapter);
		printf("	rssi: %i\n", 		  devices[i].rssi);
		printf("	protocol: %s\n", 	  devices[i].protocol);
	}	

	dbus_message_unref(msg);
	dbus_message_unref(reply);
	dbus_connection_unref(conn);
	dbus_error_free(&err);
}

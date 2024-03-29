/*
 * Copyright (C) 2008-2012 NEC Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "cc_single_link.h"


/**
 * Initializes a new list by passing the head of the list. Note that
 * the head element should be allocated on caller's stack or heap.
 *
 * @param list the head of the list.
 * @return CC_SUCCESS on success; CC_ERROR otherwise.
 */
uint32_t
create_list( list_element **list ) {
  if ( list == NULL ) {
    log_err_for_cc( "list must not be NULL" );
  }

  *list = NULL;
  return CC_SUCCESS;
}


/**
 * Inserts a new element at the head of the list.
 *
 * @param head the head of the list. This will be updated to the new element.
 * @param data the data for the new element.
 * @return CC_SUCCESS on success; CC_ERROR otherwise.
 */
uint32_t
insert_in_front( list_element **head, void *data ) {
  if ( head == NULL ) {
    log_err_for_cc( "head must not be NULL" );
  }

  list_element *old_head = *head;
  list_element *new_head = malloc( sizeof( list_element ) );

  new_head->data = data;
  *head = new_head;
  ( *head )->next = old_head;
  return CC_SUCCESS;
}


/**
 * Inserts a node before \e sibling containing \e data.
 *
 * @param head the head of the list.
 * @param sibling node to insert \e data before.
 * @param data data to put in the newly-inserted node.
 * @return CC_SUCCESS on success; CC_ERROR otherwise.
 */
uint32_t
insert_before( list_element **head, const void *sibling, void *data ) {
  if ( head == NULL ) {
    log_err_for_cc( "head must not be NULL" );
  }
   list_element *e;
  for (e = *head; e->next != NULL; e = e->next ) {
    if ( e->next->data == sibling ) {
      list_element *new_element = malloc( sizeof( list_element ) );
      new_element->next = e->next;
      new_element->data = data;
      e->next = new_element;
      return CC_SUCCESS;
    }
  }

  return CC_ERROR;
}


/**
 * Adds a new element on to the end of the list.
 *
 * @param head the head of the list.
 * @param data the data for the new element.
 * @return CC_SUCCESS on success; CC_ERROR otherwise.
 */
uint32_t
append_to_tail( list_element **head, void *data ) {
  if ( head == NULL ) {
    log_err_for_cc( "head must not be NULL" );
  }

  list_element *new_tail = malloc( sizeof( list_element ) );
  new_tail->data = data;
  new_tail->next = NULL;

  if ( *head == NULL ) {
    *head = new_tail;
    return CC_SUCCESS;
  }

  list_element *e;
  for ( e = *head; e->next != NULL; e = e->next );
  e->next = new_tail;
  return CC_SUCCESS;
}


/**
 * Gets the number of elements in a list.
 *
 * @param head the head of the list.
 * @return the number of elements in the list.
 */
unsigned int
list_length_of( const list_element *head ) {
  if ( head == NULL ) {
    return 0;
  }
  unsigned int length = 1;
  list_element *e;
  for ( e = head->next; e; e = e->next, length++ );
  return length;
}


/**
 * Calls a function for each element of a list.
 *
 * @param head the head of the list.
 * @param function the function to call with each element's data.
 * @param user_data user-data to pass to the function.
 */
void
iterate_list( list_element *head, void (*function)( void *data, void *user_data ), void *user_data ) {
  if ( head == NULL ) {
    log_err_for_cc( "head must not be NULL" );
  }
  if ( function != NULL ) {
    list_element *e;
    for (e = head; e != NULL; e = e->next ) 
	{
      (*function)( e->data, user_data );
    }
  }
}


/**
 * Finds an element in a list, using a supplied function to find the
 * desired element. It iterates over the list, calling the given
 * function which should return CC_SUCCESS when the desired element is found.
 *
 * @param head the head of the list.
 * @param function the function to call for each element. It should return CC_SUCCESS when the desired element is found.
 * @param user_data user-data passed to the function.
 * @return the found list element, or NULL if it is not found.
 */
void *
find_list_custom( list_element *head, uint32_t function( void *data, void *user_data ), void *user_data ) {
  if ( head == NULL ) {
    log_err_for_cc( "head must not be NULL" );
  }
  if ( function == NULL ) {
    log_err_for_cc( "function must not be NULL" );
  }

  void *data_found = NULL;
  list_element *e;
  for ( e = head; e != NULL; e = e->next ) {
    if ( function( e->data, user_data ) ) {
      data_found = e->data;
      break;
    }
  }
  return data_found;
}


/**
 * Removes an element from a list. If two elements contain the same
 * data, only the first is removed. If none of the elements contain
 * the data, the list is unchanged.
 *
 * @param head the head of the list.
 * @param data the data of the element to remove.
 * @return CC_SUCCESS on success; CC_ERROR otherwise.
 */
uint32_t
delete_element( list_element **head, const void *data ) {
  if ( head == NULL ) {
    log_err_for_cc( "head must not be NULL" );
  }

  list_element *e = *head;

  if ( e->data == data ) {
    *head = e->next;
    free( e );
    return CC_SUCCESS;
  }

  for ( ; e->next != NULL; e = e->next ) {
    if ( e->next->data == data ) {
      list_element *delete_me = e->next;
      e->next = e->next->next;
      free( delete_me );
      return CC_SUCCESS;
    }
  }

  return CC_ERROR;
}


/**
 * Removes all elements from a list.
 *
 * @param head the head of the list.
 * @return CC_SUCCESS on success; CC_ERROR otherwise.
 */
uint32_t
delete_list( list_element *head ) {
  list_element*e;

  for (e = head; e != NULL; ) {
    list_element *delete_me = e;
    e = e->next;
    free( delete_me );
  }
  return CC_SUCCESS;
}


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */


/***************************************************************************//**
 * @file
 *   scheduler.c
 * @author
 *   Frank McDermott
 * @date
 *   9/8/2022
 * @brief
 *   Contains all of the scheduler driver functionality
 ******************************************************************************/

//*******************************************************
// included files
//*******************************************************
#include "scheduler.h"


//*******************************************************
// static variables
//*******************************************************
static uint32_t event_scheduled;    // tracks scheduled events


//*******************************************************
// function definitions
//*******************************************************
/***************************************************************************//**
 * @brief
 *    Driver to open the scheduler
 *
 * @details
 *    Initializes the value of event_scheduled to zero.
 *
 * @note
 *    Must be an atomic operation to prevent interrupts while
 *    updating the value of the scheduler
 *
******************************************************************************/
void scheduler_open(void)
{
  // initialize events to zero
  event_scheduled = CLEAR_SCHEDULED_EVENTS;
}


/***************************************************************************//**
 * @brief
 *    Driver to add an event to the scheduler
 *
 * @details
 *    Adds a new event to the scheduler while keeping the previous event data
 *    intact
 *
 * @note
 *    Must be an atomic operation to prevent interrupts while
 *    updating the value of the scheduler
 *
 * @param[in] event
 *    32-bit unsigned integer value pertaining to the event to be scheduled
 *
******************************************************************************/
void add_scheduled_event(uint32_t event)
{
  // add event
  event_scheduled |= event;
}


/***************************************************************************//**
 * @brief
 *    Driver to remove an event from the scheduler
 *
 * @details
 *    Removed specific event from the scheduler without affecting
 *    other events that may be scheduled
 *
 * @note
 *    Must be an atomic operation to prevent interrupts while
 *    updating the value of the scheduler
 *
 * @param[in] event
 *    32-bit unsigned integer value pertaining to the event to be removed
 *    from the scheduler
 *
******************************************************************************/
void remove_scheduled_event(uint32_t event)
{
  // remove event
  event_scheduled &= ~(event);
}


/***************************************************************************//**
 * @brief
 *    Driver to retrieve all scheduled events
 *
 * @note
 *    Must be an atomic operation to prevent interrupts while
 *    updating the value of the scheduler
 *
 * @return
 *    static variable for scheduled events
 *
******************************************************************************/
uint32_t get_scheduled_events(void)
{
  return event_scheduled;
}


#include "imgUtils.c"

// This lets the driver code override the image size if it needs to. Make sure
// you don't hard-code these values anywhere!
#define SIZEX
#define SIZEX 512
#define SIZEY 512

/*---------------------------------------------------------------------------*/

/**
 * This struct contains one node of the linked list, which represents a single
 * command to the Turtle. It's field should include:
 *
 *  - cmd   : A char array of size 10 holding the command name
 *
 *  - val   : An integer that stores a parameter for the command (like forward,
 *            backward and colour).
 *
 *  - next  : A pointer to a struct of the same type, this is used for the
 *            linked list
 *
 * TODO: Complete this struct definition
 ****/

typedef struct cmdnode
{
  char cmd[10]; // 10/11('\0')???
  int val;
  struct cmdnode *next;
} CmdNode;

/*---------------------------------------------------------------------------*/

CmdNode *newCmdNode(char cmd[10], int val)
{
  /**
   * This function allocates a new CmdNode struct and initializes it's values
   * based on the input paramaters given. The next pointer is always
   * initialized to NULL.
   *
   * If the 'cmd' parameter is not a correct command, then print
   * "Invalid command.\n" and return NULL.
   *
   * Note that we will always pass in a value here, even if the
   * command doesn't need one. In this case, we can just ignore
   * it. It saves us from having to make separate functions to
   * deal with this.
   *
   * TODO: Implement this function
   */
  // cmd=penup,pendown...etc?
  // do we need to write extra if else to for new->val=val(only for fxns that take in vals) or
  // we ignore that for this fxn

  CmdNode *new = NULL;
  new = (CmdNode *)calloc(1, sizeof(CmdNode));
  if (new == NULL)
  {
    return NULL;
  }

  if ((strcmp(cmd, "penup") == 0) || (strcmp(cmd, "pendown") == 0) ||
      (strcmp(cmd, "colour") == 0) || (strcmp(cmd, "forward") == 0) ||
      (strcmp(cmd, "backward") == 0) || (strcmp(cmd, "right") == 0) ||
      (strcmp(cmd, "left") == 0))
  {
    strcpy(new->cmd, cmd);
    new->val = val;
    new->next = NULL;
    return new;
  }

  else
  {
    printf("Invalid command.\n");
  }
  return NULL;
}

/*---------------------------------------------------------------------------*/

void printCommandList(CmdNode *head)
{
  /**
   * This function prints out each command in the linked list one after the
   * other. Each command MUST also have a line number printed before it, this
   * is what you will be using to modify / delete them. To do this, initialize
   * a counter and then increment it for each command.
   *
   * Depending on whether or not the command needs an additional value
   * (like forward, backward and colour), use one of the following statements
   * to print out the information for each node:
   *            [ The format is "linenumber: command value" ]
   *
   * printf("%3d: %s %d\n", ... );     [With a value]
   *
   * printf("%3d: %s\n", ... );        [Without a value]
   *
   * Obviously, you also need to pass in the correct parameters to the print
   * function yourself, this is just so you have the correct format.
   *
   * TODO: Implement this function
   */
  int line_num = 0;
  while (head != NULL)
  {
    if ((strcmp(head->cmd, "colour") == 0) || (strcmp(head->cmd, "forward") == 0) ||
        (strcmp(head->cmd, "backward") == 0))
    {
      printf("%3d: %s %d\n", line_num, head->cmd, head->val);
    }
    else if ((strcmp(head->cmd, "penup") == 0) || (strcmp(head->cmd, "pendown") == 0) ||
             (strcmp(head->cmd, "right") == 0) || (strcmp(head->cmd, "left") == 0))
    {
      printf("%3d: %s\n", line_num, head->cmd);
    }
    else
    {
      return;
    }
    line_num++;
    head = head->next;
  }
  return;
}

/*---------------------------------------------------------------------------*/

void queryByCommand(CmdNode *head, char cmd[10])
{
  /**
   * This function looks for commands in the linked list that match the input
   * query. It prints them out in the same format as the printCommandList()
   * function.
   *
   * Make sure that the line number of the commands that match is the same as
   * the line number that would be printed by the printCommandList() function.
   *
   * --------------------------------------------------------------------------
   *
   * For instance, if your printCommandList function outputs
   *
   *    0: penup
   *    1: forward 200
   *    2: right
   *    3: forward 50
   *
   * Then, if this function is called with the same list and cmd = "forward",
   * then your output here should be
   *
   *    1: forward 200
   *    3: forward 50
   *
   * TODO: Implement this function
   */
  // print??
  CmdNode *curr = NULL;
  curr = head;
  int line_num = 0;
  while (curr != NULL)
  {
    if (strcmp(curr->cmd, cmd) == 0)
    {
      if ((strcmp(curr->cmd, "colour") == 0) || (strcmp(curr->cmd, "forward") == 0) ||
          (strcmp(curr->cmd, "backward") == 0))
      {
        printf("%3d: %s %d\n", line_num, curr->cmd, curr->val);
      }
      else if ((strcmp(curr->cmd, "penup") == 0) || (strcmp(curr->cmd, "pendown") == 0) ||
               (strcmp(curr->cmd, "right") == 0) || (strcmp(curr->cmd, "left") == 0))
      {
        printf("%3d: %s\n", line_num, curr->cmd);
      }
    }
    line_num++;
    curr = curr->next;
  }
  return;
}

/*---------------------------------------------------------------------------*/

int countCommands(CmdNode *head)
{
  /**
   * This function counts and returns the length of the linked list. It
   * requires list traversal.
   *
   * TODO: Implement this function
   */
  CmdNode *curr = head;
  int count = 0;
  while (curr != NULL)
  {
    count++;
    curr = curr->next;
  }
  return count;
}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommand(CmdNode *head, CmdNode *new_CmdNode)
{
  /**
   * This function inserts the node new_CmdNode *at the tail* of the linked
   * list. (You are adding a command at the end).
   *
   * If head == NULL, then the linked list is still empty.
   *
   * It returns a pointer to the head of the linked list with the new node
   * added into it.
   *
   * TODO: Implement this function
   */

  if (NULL == head)
  {
    return new_CmdNode; // means that if there's no head, no inserting new_cmdnode??
  }
  CmdNode *curr = head;
  while (NULL != curr->next)
  {
    curr = curr->next;
  }
  curr->next = new_CmdNode;
  // curr=curr->next;
  // curr->next=NULL;------------??
  return head;
}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommandBefore(CmdNode *head, CmdNode *new_CmdNode, int cmdNum)
{
  /**
   * This function inserts a new node *before* a given Node in the linked list.
   *
   * 'cmdNum' is an integer that corresponds to the line number of a command
   * from the printCommandList() function. Your task is to insert new_CmdNode
   * *before* the corresponding node in the linked list.
   *
   * --------------------------------------------------------------------------
   *
   * For instance, if your initial list was
   *
   *    0: penup
   *    1: forward 200
   *    2: right
   *    3: forward 50
   *
   * And you added "pendown" before cmdNum = 2, then you will have
   *
   *    0: penup
   *    1: forward 200
   *    2: pendown
   *    3: right
   *    4: forward 50
   *
   * --------------------------------------------------------------------------
   *
   * If there is no command with the given cmdNum (cmdNum >= list size),
   * then print "Invalid Command Number.\n" to the screen and *do not*
   * insert the new node.
   *
   * Returns a pointer to the head of the linked list with the new node added
   * into it.
   *
   * TODO: Implement this function
   */
  //[head]  [   ] N [   ]  [   ] |
  //          p       c
  if (head == NULL)
  {
    return NULL; // returns NULL or new_CmdNode?
  }
  int len = countCommands(head);
  if (cmdNum >= len || cmdNum < 0)
  {
    printf("Invalid Command Number.\n");
    return head;
  }
  if (cmdNum == 0)
  {
    new_CmdNode->next = head;
    return new_CmdNode;
  }
  int line_num = 1;
  CmdNode *curr = head->next;
  CmdNode *prev = head;
  while (prev != NULL)
  {
    if (line_num == cmdNum)
    {
      prev->next = new_CmdNode;
      new_CmdNode->next = curr;
      return head;
    }
    line_num++;
    prev = prev->next;
    curr = curr->next;
  }
  return head;
}

/*---------------------------------------------------------------------------*/

void updateCommand(CmdNode *head, int cmdNum, char cmd[10], int val)
{
  /**
   * This function updates a specific node in the linked list based on the
   * input parameters.
   *
   * 'cmdNum' is an integer that corresponds to the line number of a command
   * from the printCommandList() function. Your task is to update the 'cmd' and
   * 'val' fields of this node.
   *
   * If there is no command with the given cmdNum, then print
   * "Invalid Command Number.\n" to the screen, and if 'cmd' is not a correct
   * command, then print "Invalid command.\n". In both these cases, do *not*
   * modify the list.
   *
   * TODO: Implement this function
   */
  int len = countCommands(head);
  CmdNode *curr = head;
  if (head == NULL)
  {
    return;
  }
  if (cmdNum >= len || cmdNum < 0)
  {
    printf("Invalid Command Number.\n");
    return;
  }
  int l_num = 0;
  while (curr != NULL)
  {
    if (l_num == cmdNum)
    {
      if ((strcmp(cmd, "penup") == 0) || (strcmp(cmd, "pendown") == 0) ||
          (strcmp(cmd, "colour") == 0) || (strcmp(cmd, "forward") == 0) ||
          (strcmp(cmd, "backward") == 0) || (strcmp(cmd, "right") == 0) ||
          (strcmp(cmd, "left") == 0))
      {
        strcpy(curr->cmd, cmd);
        curr->val = val;
      }
      else
      {
        printf("Invalid command.\n");
        return;
      }
    }
    l_num++;
    curr = curr->next;
  }
  return;
}

/*---------------------------------------------------------------------------*/

CmdNode *deleteCommand(CmdNode *head, int cmdNum)
{
  /**
   * This function deletes the node from the linked list that corresponds to
   * the line number cmdNum. If there is no command with the given cmdNum, then
   * the function does nothing.
   *
   * Returns a pointer to the head of the linked list (which may have changed
   * as a result of the deletion)
   *
   * TODO: Implement this function
   */
  CmdNode *curr = head->next;
  CmdNode *prev = head;
  int l_num = 1;
  int len = countCommands(head);
  if (head == NULL)
  {
    return NULL;
  }
  if (cmdNum >= len || cmdNum < 0)
  {
    return head;
  }
  if (cmdNum == 0)
  {
    free(prev);
    return head->next;
  }
  //[head]  [   ]  [   ]  [   ]  |
  //                 p      c
  while (curr != NULL)
  {
    if (l_num == cmdNum)
    {
      prev->next = curr->next;
      free(curr);
    }
    l_num++;
    prev = prev->next;
    curr = curr->next;
  }
  return head;
}

/*---------------------------------------------------------------------------*/

CmdNode *deleteCommandList(CmdNode *head)
{
  /**
   * This function deletes the linked list of commands, releasing all the
   * memory allocated to the nodes in the linked list.
   *
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   *
   * TODO: Implement this function
   */
  if (head == NULL)
  {
    return NULL;
  }
  CmdNode *curr = NULL;
  CmdNode *prev = head;
  while (prev != NULL)
  {
    curr = prev->next;
    free(prev);
    prev = curr;
  }
  return NULL;
}

/*---------------------------------------------------------------------------*/

void run(Image *im, CmdNode *head, int *endX, int *endY)
{
  /**
   * This function runs the list of commands to move the turtle around and draw
   * the image, and returns the final position of the turtle in the variables
   * endX and endY.
   *
   * --------------------------------------------------------------------------
   *
   * NOTE: In the image we work with, the top-left pixel is (0,0),
   *       - x increases as you go right, up till SIZEX-1
   *       - y increases as you go down, up till SIZEY-1
   *
   *                 (0,0)                 (SIZEX-1, 0)
   *                   x------------------------x
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |          IMAGE         |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   x------------------------x
   *             (0, SIZEY-1)            (SIZEX-1, SIZEY-1)
   *
   * The image is in grayscale (black and white), so the colours are numbers
   * from [0-255] where 0 is black, 255 is white, and the values in between
   * are varying levels of gray.
   *
   * You need to understand how the (x,y) values are stored so you know how
   * they should be updated when you move (down means y increases, etc). You do
   * not need to use the 'im' variable for anything other than passing it into
   * the drawLine() function described below.
   *
   * --------------------------------------------------------------------------
   *
   * Here's the setup - There is a turtle (with a pen) that walks along the
   * image. When the pen is down (on the paper), it draws a line along the path
   * that it walks on. (If you want to play around with this, consider looking
   * at the `turtle` library in python!)
   *
   * The turtle initially starts at pixel (0, 0) [at the top left],
   * facing right (in the positive x direction). The pen starts off
   * as `down`, with the default colour being black (0).
   *
   * You need to go through the linked list and 'run' the commands to keep
   * track of the turtles position, and draw the appropriate lines. Here is
   * what each command should do:
   *
   *  - penup          : Put the pen up (stop drawing)
   *  - pendown        : Put the pen down (start / continue drawing)
   *  - colour <val>   : Draw lines in colour <val> from now on
   *  - forward <val>  : Move the turtle forward <val> steps (pixels)
   *                     in the direction it is facing.
   *  - backward <val> : Same as above, except move backwards
   *  - right          : Turn the turtle to the right by 90 degrees
   *  - left           : Turn the turtle to the left by 90 degrees
   *
   * NOTE: Make sure that you do *not* go outside the image. For this, set the
   * maximum and minimum values of x and y to be 0 and SIZEX-1 / SIZEY-1
   * respectively.
   *
   * For instance, if the turtle is at (0,0) facing right, and your command is
   * `forward 100000`, it will only go forward till (SIZEX-1, 0), and end
   * up at the rightmost pixel in that row.
   *
   * IMPORTANT: Once you are done with all the commands, make sure you save the
   * final (x,y) location of the turtle into the variables endX and endY.
   *
   * --------------------------------------------------------------------------
   *
   * We have already implemented a drawLine() function (in imgUtils.c) which
   * you should use to actually draw the lines. It takes in the following:
   *
   *      - a pointer to an image struct (use 'im')
   *      - (x,y) location of start point
   *      - (x,y) location of end point
   *      - a colour to draw the line in [0-255]
   *
   * Note that this function only draws horizontal and vertical lines, so
   * either the x values or the y values of both points must be the same.
   * Both these points *must* also be within the image.
   *          [ 0 <= x < SIZEX,  0 <= y < SIZEY ]
   *
   *
   * TODO: Implement this function
   */

  int startX = 0, startY = 0, color = 0, up = 0;
  *(endX) = 0;
  *(endY) = 0;
  CmdNode *curr = head;
  if (head == NULL)
  {
    return;
  }
  int DIRECTION = -2, WEST = -1, EAST = -2, NORTH = -3, SOUTH = -4;
  while (curr != NULL)
  {
    int value = curr->val;
    if (strcmp(curr->cmd, "pendown") == 0)
    {
      up = 0;
    }
    if (strcmp(curr->cmd, "penup") == 0)
    {
      up = 1;
    }
    if (strcmp(curr->cmd, "forward") == 0)
    {
      if (DIRECTION == EAST)
      {
        *(endX) = startX + value;
      }
      else if (DIRECTION == WEST)
      {
        *(endX) = startX - value;
      }
      else if (DIRECTION == NORTH)
      {
        *(endY) = startY - value;
      }
      else if (DIRECTION == SOUTH)
      {
        *(endY) = startY + value;
      }
    }
    if (strcmp(curr->cmd, "backward") == 0)
    {
      if (DIRECTION == WEST)
      {
        *(endX) = startX + value;
      }
      else if (DIRECTION == EAST)
      {
        *(endX) = startX - value;
      }
      else if (DIRECTION == SOUTH)
      {
        *(endY) = startY - value;
      }
      else if (DIRECTION == NORTH)
      {
        *(endY) = startY + value;
      }
    }
    if ((*endX) > SIZEX - 1)
    {
      *(endX) = SIZEX - 1;
    }
    if ((*endX) < 0)
    {
      *(endX) = 0;
    }
    if (*(endY) > SIZEY - 1)
    {
      *(endY) = SIZEY - 1;
    }
    if (*(endY) < 0)
    {
      *(endY) = 0;
    }
    if (strcmp(curr->cmd, "right") == 0)
    {
      if (DIRECTION == NORTH)
      {
        DIRECTION = EAST;
      }
      else if (DIRECTION == SOUTH)
      {
        DIRECTION = WEST;
      }
      else if (DIRECTION == EAST)
      {
        DIRECTION = SOUTH;
      }
      else if (DIRECTION == WEST)
      {
        DIRECTION = NORTH;
      }
    }
    else if (strcmp(curr->cmd, "left") == 0)
    {
      if (DIRECTION == NORTH)
      {
        DIRECTION = WEST;
      }
      else if (DIRECTION == SOUTH)
      {
        DIRECTION = EAST;
      }
      else if (DIRECTION == EAST)
      {
        DIRECTION = NORTH;
      }
      else if (DIRECTION == WEST)
      {
        DIRECTION = SOUTH;
      }
    }
    if (strcmp(curr->cmd, "colour") == 0)
    {
      if ((curr->val) > -1 && (curr->val) < 256)
      {
        color = (curr->val);
      }
    }
    if (up == 0)
    {
      drawLine(im, startX, startY, *(endX), *(endY), color);
    }
    startX = *(endX);
    startY = *(endY);
    curr = curr->next;
  }

  return;
}
/*---------------------------------------------------------------------------*/
// All done!
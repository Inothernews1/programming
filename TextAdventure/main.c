#include <stdio.h>
#include <stdlib.h>
#include "tadv.h"

char buffer[80];

int main () {
  int terminate = 0;
  int trunk = 0;
  char *ptr;

  node *glowCloud = nodeMake("NEVERMIND THAT ALL HAIL THE GLOW CLOUD\nGLOW CLOUD END", 0);
  glowCloud->type = NODE_END;

  node *ultraRelief = nodeMake("You start to shamble your way towards the kitchen. One step at a time, you tell yourself. One, two, three, fo- AGGHH! You fall down. You slipped on something... What was that? You see a tiny little figure just out of the corner of your eye run away. At this point, your headache seems to be replaced by curiosity. You hear a clang near the TV. What do you do?", 4, "ALL HAIL THE GLOW CLOUD", glowCloud, "ALL HAIL THE GLOW CLOUD", glowCloud, "ALL HAIL THE GLOW CLOUD", glowCloud, "ALL HAIL THE GLOW CLOUD", glowCloud);

  node *proPainEnd = nodeMake("Surprisingly, you deciding to wait it out results in your death. That's too bad too, because you feel as if you missed out on a fantasical adventure over a simple headache. Also because you are dead.\nPROPAIN END", 0);
  proPainEnd->type = NODE_END;

  node *proPain = nodeMake("'Screw it.' you say, and shove the ProPain in your mouth. It tastes bad. It tastes really bad. Holy s**t, it's making you want to vomit. But you swallow anyways. Uggh, that was awful, but at least the headache is better. Just out of curiosity, you check the bottle... Oh no... It expired 2 months ago... You start to rush out of the bathroom. What do you do?", 1, "Wait it out, you body rids itself of toxins, right?", proPainEnd);

  node *meds = nodeMake("You slowly get up. Every bone in your body tells you not to, but you do anyways. You shuffle your way over to the medicine cabinet, and open it up. The only medicine in here is ProPain, but you need UltraRelief... which is all the way back in the kitchen.", 2, "Take the ProPain.", proPain, "Go to the kitchen to get the UltraRelief.", ultraRelief);

  node *lieThereEnd = nodeMake("You keep waitng. Another hour passes. Two. Then three. Then something very peculier happens. The television switched to another station. On it was a man reporting. He was saying something, but you couldn't quite make it out over the loud ringing sound. You sat up a little. Your vision was blurred but you could make out weird red marks on your couch. Strange. Maybe you should take some medication, the headache is really star-\nLAZY END", 0);
  lieThereEnd->type = NODE_END;

  node *lieThere = nodeMake("You decide to wait a little longer before getting up. An hour passes.", 2, "Continue to lie there.", lieThereEnd, "Get up and take some medication.", meds);

  node *start = nodeMake("You wake up with a massive headache. Last night you did some serious partying. You did some things that you probably shouldn't have. You don't quite know why the TV is on, but it is nevertheless. But none of that matters now because you have a headache. A raw, eye-shattering, ear splitting headache. You should take something, anything, for this massive headache, but you're extremely tired.", 2, "Lie there.", lieThere, "Get up and take some medication.", meds);

  node *currNode = start;

  while (!terminate) {
    if (currNode->type != NODE_END) {
      do {
        nodeDisplay(currNode);
        fgets(buffer, 80, stdin);
        trunk = strtol(buffer, &ptr, 10);
      } while ((trunk > currNode->optNum) || (trunk < 1));
      
      currNode = nodeChange(currNode, trunk);
    } else {
      nodeDisplay(currNode);
      terminate = 1;
    }
  }

  getchar();

  return 0;
}

# Design Decisions

## Internal Structure

## Prime Table Size

## Finding a Real Collision

Pick any bucket in your `modHash` table whose chain length is at least 2.
List the words in that bucket. Do they share the same letters (in any
order), or at least the same ASCII sum? Explain in one or two sentences
why `modHash` collapsed them into the same bucket, and check whether
`hornerHash` places those same words in different buckets. This is
evidence you gathered yourself from your own output.

## Hash Function Comparison

Tell the story your numbers tell. Include the actual diagnostic numbers
from both Section A and Section B. Do not just list them.

- What does `modHash` ignore that `hornerHash` accounts for?
- Which function produced a more even distribution, and how do you know?
- What would happen to lookup performance in the worst bucket under
  each function?
- Use your actual longest chain and average chain length to make the
  argument.

## Interesting Observations

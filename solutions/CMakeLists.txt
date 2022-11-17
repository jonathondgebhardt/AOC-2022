# Since our day solutions are one directory deeper, we have to echo the root AOC variables
# down to subdirectories.
set(${AOC_SOURCE_H}
  AOC_SOURCE_H
  PARENT_SCOPE
)

set(${AOC_SOURCE}
  AOC_SOURCE
  PARENT_SCOPE
)

# Now that we've visited subdirectories, echo the AOC variables back up to the parent scope.
set(${AOC_SOURCE_H}
  AOC_SOURCE_H
  PARENT_SCOPE
)

set(${AOC_SOURCE}
  AOC_SOURCE
  PARENT_SCOPE
)

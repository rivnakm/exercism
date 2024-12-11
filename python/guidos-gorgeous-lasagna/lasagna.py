"""Functions used in preparing Guido's gorgeous lasagna.

Learn about Guido, the creator of the Python language:
https://en.wikipedia.org/wiki/Guido_van_Rossum

This is a module docstring, used to describe the functionality
of a module and its functions and/or classes.
"""

EXPECTED_BAKE_TIME = 40
PREPARATION_TIME = 2


def bake_time_remaining(elapsed_bake_time: int) -> int:
    """Calculate the bake time remaining.

    Args:
        elapsed_bake_time: The baking time already elapsed.

    Returns:
        The remaining bake time (in minutes) derived from 'EXPECTED_BAKE_TIME'.

    Function that takes the actual minutes the lasagna has been in the oven as
    an argument and returns how many minutes the lasagna still needs to bake
    based on the `EXPECTED_BAKE_TIME`.
    """
    return EXPECTED_BAKE_TIME - elapsed_bake_time


def preparation_time_in_minutes(number_of_layers: int) -> int:
    """

    Args:
        number_of_layers: Number of layers in the lasagna

    Returns:
        The total preparation time

    Calculates how long the lasagna will take to prepare based on the number of layers
    """
    return PREPARATION_TIME * number_of_layers


def elapsed_time_in_minutes(number_of_layers: int, elapsed_bake_time: int) -> int:
    """

    Args:
        number_of_layers: Number of layers in the lasagna
        elapsed_bake_time: The baking time already elapsed

    Returns:
        Total elapsed time, baking and preparation

    """
    return preparation_time_in_minutes(number_of_layers) + elapsed_bake_time

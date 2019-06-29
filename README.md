# Smart Home De-Centralised

## Switches

`switches` defines the switches mapping to buttons.

## Targets

`targets` define what devices should be turned on/off and with what rules.

Rule values:
0. toggle
1. toggle, delayed off by `rule_value` seconds of time
2. turn on, for `rule_value` seconds of time (auto off after `rule_value` seconds of time)

## Connections

`connections` defines mapping between `switches` and `targets`, use indexes of the arrays.

# Smart Home De-Centralised

Arduino sketch to manage "smart" home, allows many to many mappings, any switch can change any target.

Allows configuring additional rules for targets with delayed off or limited time on.

## Configuration

Edit `configuration.h` and add your values

### Switches

`switches` defines the switches mapping to buttons.

### Targets

`targets` define what devices should be turned on/off and with what rules.

Rule values:
0. toggle
1. toggle, delayed off by `rule_value` seconds of time
2. turn on, for `rule_value` seconds of time (auto off after `rule_value` seconds of time)

### Connections

`connections` defines mapping between `switches` and `targets`, use indexes of the arrays.

## Development

Open a PR with your changes, make sure you check the code is working.

## Authors

- Michal Papis <mpapis@gmail.com>

## License

[GNU LESSER GENERAL PUBLIC LICENSE](LICENSE.txt)

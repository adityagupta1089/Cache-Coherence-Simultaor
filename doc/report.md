# Testing Report

## General testing

A file `gen.trace` was used and the testcases thus peformed are described below (line number of file)

- Eviction testing - \#19 - pass

## MSI

A file `MSI.trace` was used and the testcases thus performed are described below (line number of file, e.g. \#x)

|          | Write Hit                                | Write Miss                                  | Read Hit                | Read Miss                                                    | Bus Read Miss               | Bus Write Miss                | Invalid                  |
| -------- | ---------------------------------------- | ------------------------------------------- | ----------------------- | ------------------------------------------------------------ | --------------------------- | ----------------------------- | ------------------------ |
| Modified | \#4  - Write data - pass                 | Not possible                                | \#2 - Read data - pass  | Not possible                                                 | \#3 - service block - pass  | \#7 - invalidated data - pass | \#7 - Invalidated - pass |
| Shared   | \#4 - Write and invalidate others - pass | Not possible                                | \#15 - Read data - pass | Not possible                                                 | \#11 - service block - pass | \#9 - invalidate block - pass | \#4 - Invalidated - pass |
| Invalid  | Not possible                             | \#7 - Write data and send invalidate - pass | Not Possible            | \#5 - Sent read miss on bus & get back data - pass           | Ignored                     | Ignored                       | Ignored                  |
| Absent   | Not Possible                             | \\#14 - Wrote data - pass                   | Not Possible            | \#1 - Fetch from storage - pass, \#3 - fetch from other cache - pass | Ignored                     | Ignored                       | Ignored                  |

### Other cases checked

- Sharing with value in multiple caches - \#11 - only one cache services - pass
- Multiple invalidation - \#9 - pass

## MESI

A file `MESI.trace` was used and the testcases thus performed are described below (line number of file, e.g. \#x)

|                | Modified                                             | Exclusive                                       | Shared                                        | Invalid                                          | Absent                                                       |
| -------------- | ---------------------------------------------------- | ----------------------------------------------- | --------------------------------------------- | ------------------------------------------------ | ------------------------------------------------------------ |
| Read hit       | \#5 - read data - pass                               | \#2 - read data - pass                          | \#7 - read data - pass                        | Not possible                                     | Not possible                                                 |
| Read miss      | Not possible                                         | Not possible                                    | Not possible                                  | \#12 - send bus request and receive block - pass | \#1 - fetch from secondaey storage  - pass, \#6 - fetch from other cache - pass |
| Write hit      | \#8 - wrote data (possible invalidate others) - pass | \#4 - wrote data and changed to modified - pass | \#9 - wrote data and invalidate others - pass | Not possible                                     | Not possible                                                 |
| Write miss     | Not possible                                         | Not possible                                    | Not possible                                  | \#14 - write data and invalidate others - pass   | \#3 - write data - pass                                      |
| Bus Read miss  | \#7 - service block - pass                           | \#5 - service block - pass                      | \#16 - service block - pass                   | Ignored                                          | Ignored                                                      |
| Bus Write miss | \#20 - invalidated - pass                            | \#18 - invalidated - pass                       | \#19 - invalidated block - pass               | Ignored                                          | Ignored                                                      |
| Invalidate     | \#14 - invalidate - pass                             | \#18 - invalidated - pass                       | \#9 - invalidated - pass                      | Ignored                                          | Ignored                                                      |

### Other cases checked

- Sharing with value in multiple caches - \#15 - only one cache services - pass
- Multiple invalidation - \#18 - pass

## MOESI

A file `MOESI.trace` was used and the testcases thus performed are described below (line number of file, e.g. \#x)

|                | Modified                                       | Owned                                                        | Exclusive                                     | Shared                                                     | Invalid                                         | Absent                                                       |
| -------------- | ---------------------------------------------- | ------------------------------------------------------------ | --------------------------------------------- | ---------------------------------------------------------- | ----------------------------------------------- | ------------------------------------------------------------ |
| Read hit       | \#5 - read data - pass                         | \#9 - read data - pass                                       | \#3 - read data - pass                        | \#8 - read data - pass                                     | Not possible                                    | Not possible                                                 |
| Read miss      | Not possible                                   | Not possible                                                 | Not possible                                  | Not possible                                               | \#11 - send read miss and get back block - pass | \#1 - fetch from secondary storage - pass, #7 - read from other cache - pass |
| Write hit      | \#6 - wrote data  and invalidate others - pass | \#10 - change to modifed, no write back, invalidate others - pass | \#4 - write data and invalidate others - pass | \#12 - write block, invalidate others - pass               | Not possible                                    | Not possible                                                 |
| Write miss     | Not possible                                   | Not possible                                                 | Not possible                                  | Not possible                                               | \#19 - send write miss and write block - pass   | \#2 - fetch from secondary storage - pass                    |
| Bus Read miss  | \#11 - service block and change to owned       | \#14 - shared cache block - pass                             | \#7 - service data, change to owned - pass    | \#14 - allow other (owned) cache to service request - pass | Ignored                                         | Ignored                                                      |
| Bus Write miss | \#15 - invalidate block - pass                 | \#16 - invalidated block and wrote back - pass               | \#18 - invalidated cache block - pass         | \#16 - invalidate cache block - pass                       | Ignored                                         | Ignored                                                      |
| Invalidate     | \#15 - invalidated - pass                      | \#16 - invalidated - pass                                    | \#18 - invalidated - pass                     | \#16 - invalidated - pass                                  | Ignored                                         | Ignored                                                      |

### Other cases checked

- Sharing with value in multiple caches and one owned - \#14 - only owned cache services - pass
- Multiple invalidation - \#16 - pass
- Write back by owned state - \#14 - pass
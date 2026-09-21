<sub>_[(How version numbering works in all my programs.)](https://github.com/lunanerdderg/lunanerdderg.github.io/blob/main/version-numbering.md)_</sub> | 
<sub>_[(My policy on A.I. in my programs.)](https://github.com/lunanerdderg/lunanerdderg.github.io/blob/main/ai-use-policy.txt)_</sub>

# Building

`BanyanChart.cbp` is a [Code::Blocks](https://www.codeblocks.org/downloads/binaries/) solution file, so you will need that software to open the project. Converting to another solution format probably won't work, since this project uses the Code::Blocks-exclusive plugin [wxSmith](#Uses).

## Ubuntu

This project requires installation of `libwxgtk3.2-dev` if you run Ubuntu. It is available with this command: 

```
sudo apt update && sudo apt install -y libwxgtk3.2-dev
```

# License

You may view the GNU General Public License v3.0 [here](https://github.com/lunanerdderg/Reefbackend/blob/main/LICENSE), but the TL;DR is that you can use this project for whatever you like, as long as:

* You credit me by including a copyright notice
* Your project is open-source
* Your project uses a [GPL](https://choosealicense.com/licenses/gpl-3.0/) or [AGPL](https://choosealicense.com/licenses/agpl-3.0/) GNU license
* You state the changes you made
* You don't infringe on any relevant trademarks

_(This is a simplified summary of the license and should not be taken as legal advice. Please consult a lawyer before taking any action.)_

#### Uses:
* [wxWidgets (3.2.0)](https://github.com/wxWidgets/wxWidgets/tree/v3.2.0) uses a [modified GNU Library General Public License](https://github.com/wxWidgets/wxWidgets/blob/v3.2.0/docs/licence.txt)
* [wxSmith](https://wxsmithaddons.sourceforge.net/) is under the [GNU General Public License](http://www.gnu.org/licenses/gpl.html)

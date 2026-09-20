<sub>_[(How version numbering works in all my programs.)](https://github.com/lunanerdderg/lunanerdderg.github.io/blob/main/version-numbering.md)_</sub> | 
<sub>_[(My policy on A.I. in my programs.)](https://github.com/lunanerdderg/lunanerdderg.github.io/blob/main/ai-use-policy.txt)_</sub>

# Building

`BanyanChart.cbp` is a [Code::Blocks](https://www.codeblocks.org/downloads/binaries/) solution file, so you will need that software to open the project. Converters probably won't work, since this project uses the Code::Blocks-exclusive plugin [wxSmith](#Dependencies:).

## Ubuntu

This project requires installation of `libwxgtk3.2-dev` if you run Ubuntu. It is available with this command: 

```
sudo apt update && sudo apt install -y libwxgtk3.2-dev
```

# License

You may view the GNU General Public License v3.0 [here](https://github.com/lunanerdderg/Reefbackend/blob/main/LICENSE), but the TL;DR is that you can use this project for whatever you like, as long as:

* You credit me
* Your project is open-source
* Your project uses a [GNU license](https://choosealicense.com/licenses/)
* You state the changes you made (which will most likely happen anyway if you write a descriptive README or description for your project)

_(This is a simplified summary of the license and should not be taken as legal advice. Please consult a lawyer before taking any action.)_

#### Dependencies:
* [wxWidgets (3.2.0)](https://github.com/wxWidgets/wxWidgets/tree/v3.2.0) uses a [modified GNU LGPL license](https://github.com/wxWidgets/wxWidgets/blob/v3.2.0/docs/licence.txt)
* [wxSmith](https://wxsmithaddons.sourceforge.net/) is under the [GNU General Public License](http://www.gnu.org/licenses/gpl.html)

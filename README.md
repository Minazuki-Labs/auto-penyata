<div align="center">

<img width="650" alt="Banner" src="https://github.com/user-attachments/assets/3bb61671-4624-4b56-b8e9-a60626c0de30" />

[![Release version](https://img.shields.io/github/v/release/JuneMinazuki/auto-penyata?color=brightgreen&label=Download&style=for-the-badge)](#installation "Installation")

</div>

<p align="center">
  A desktop application that will create "Akaun Perdagangan dan Untung Rugi" and "Penyata Kedudukan Kewangan" as pdf file.
  <br>
  <br>
  <a href="#key-features">Key Features</a> •
  <a href="#getting-started">Getting Started</a> •
  <a href="#prerequisites">Prerequisites</a> •
  <a href="#contributing">Contributing</a> •
  <a href="#license">License</a>
</p>

## About The Project
**'auto-penyata'** is a simple desktop application designed to help Prinsip Perakaunan students generate key financial statements.

The application allows you to input a trial balance (Imbangan Duga) and any necessary adjustments (Pelarasan) to automatically produce:

1. Akaun Perdagangan dan Untung Rugi (APUR)
2. Penyata Kedudukan Kewangan (PKK)

These statements can then be exported as a clean, professional PDF file.

## Key Features

* 🚀 **Instant Report Generation:** Produce a complete APUR and PKK in PDF format with just a few clicks.
* ✅ **Auto-Balancing Check:** The application automatically verifies that your Statement of Financial Position is balanced and alerts you to any discrepancies.
* 📄 **Export & Print Ready:** The generated PDFs are perfectly formatted for A4 pages, ready to be printed, attached to emails, or saved for your records.

## Getting Started

<div align="center">
<img width="899" height="632" alt="Screenshot of Auto Penyata" src="https://github.com/user-attachments/assets/750d6249-9bf6-42b7-add2-71636752ad7f" />
</div>

1. **Setup:** Enter your business name and the accounting period end date.
2. **Input:** Enter all the accounts and balances from your Imbangan Duga.
3. **Adjust:** Add any adjustments (Pelarasan) like closing stock, depreciation, accruals, etc.
4. **Check:** Check the status bar to ensure the debit and credit is balance.
5. **Export:** Save the final reports as a PDF.

**[This detailed guide](https://github.com/JuneMinazuki/auto-penyata/wiki/User-Guid)** will walk you through the entire process of creating your financial statements.

## Installation

This is the easiest way to install. Click on your computer operating system below:

[![MacOS](https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=apple&logoColor=white)](https://github.com/JuneMinazuki/auto-penyata/releases/download/v1.0.1/AutoPenyata-MacOS.dmg)
[![Source Tarball](https://img.shields.io/badge/-Source_tar-green.svg?style=for-the-badge)](https://github.com/JuneMinazuki/auto-penyata/archive/refs/tags/v1.0.1.tar.gz)
[![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)](https://github.com/JuneMinazuki/auto-penyata/releases/download/v1.0.1/AutoPenyata-Windows.zip)

1. Go to the Releases page of this repository.
2. Find the latest release, which is `v1.0`.
3. Under the "Assets" section, download the app for your operating system,
4. Run the installer and follow the on-screen instructions.

If you wish to build from source, you can refer to **[this page](https://github.com/JuneMinazuki/auto-penyata/wiki/Contributing#building-from-source)** for detail instruction.

## Prerequisites
To build the project locally, you will need to set up the development environment.

* [Git](https://git-scm.com/)
* [C++ Compiler](https://visualstudio.microsoft.com/vs/features/cplusplus/) (e.g., MSVC on Windows, GCC/Clang on Linux)
* [Qt Framework (Version 6.x or newer)](https://www.qt.io/download)
    * Make sure to install the `Qt 6` core libraries and `Qt Creator`.
* [CMake](https://cmake.org/download/)

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. We welcome contributions to help improve this application! Whether you're fixing a bug, adding a new feature, or improving the documentation, **your help is appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".

1.  **Fork** the Project
2.  Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3.  Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4.  Push to the Branch (`git push origin feature/AmazingFeature`)
5.  Open a **Pull Request** from your branch to the `main` branch of this project
6.  Describe your changes clearly in the Pull Request

For more information, you can refer to the **[Contribution Guidelines on the Wiki](https://github.com/JuneMinazuki/auto-penyata/wiki/Contributing)**.

This page has all the details on our development workflow, how to set up your environment, and how to submit your changes. You can also open an **[Issue](https://github.com/JuneMinazuki/auto-penyata/issues)** to discuss your ideas.

## License

Distributed under the GPL-3.0 License. See `LICENSE` file for more information.

# VERIFICXX
#### Video Demo: url
#### Description: 

Verificxx is a multipurpose library designed for performing comprehensive validations on any kind of data represented as strings. Its primary goal is to provide a robust and flexible system that ensures data integrity, consistency, and conformity across different contexts, ranging from simple single-value checks to complex processes where multiple columns and validation rules must be applied automatically. The library supports two main approaches for validation. The first one is based on chaining predefined functions, each responsible for verifying a specific characteristic of the data, such as whether it is alphabetic, numeric, alphanumeric, complies with an email pattern, or respects length restrictions, uppercase or lowercase requirements, or specific substrings. This approach allows developers to build validation pipelines explicitly, combining rules as needed and receiving immediate feedback for each evaluation. The second approach relies on loading a JSON file that describes, in a structured way, the rules applicable to each column or data field. This method separates the definition of the validation schema from the execution logic, enabling the library to adapt to different datasets without recompiling the code. Users simply define the column names, the rules associated with each column, and optionally whether empty values are allowed. Once the schema is loaded, validation can be executed with a single call, providing detailed results for each column, including information on which rule failed and which value did not meet the specification.

The architecture of Verificxx is largely based on the hexagonal architecture pattern, also known as Ports and Adapters. This design choice was made to keep the business logic core isolated from infrastructure details and from the various data input and output channels. In practice, the project is organized into specific folders for adapters and services. Adapters handle interactions with external elements, such as reading JSON files containing the validation schema, while services centralize the business logic, in this case, the application of validation rules on the data values. This pattern ensures that changes in the way data is obtained—such as switching from local files to a cloud storage system—do not affect the central validation logic, improving maintainability and scalability. Furthermore, following clean code principles, different files are used for constants, error messages, and data structures, which makes the code easier to understand and reduces complexity when making modifications or extensions.

The development of Verificxx was motivated by a practical need observed in my current work: working with data pipelines that process large volumes of information and require exhaustive validations to ensure data quality. The previous experience was primarily in Python, a language that, while extremely flexible and excellent for prototyping, may not provide the same execution efficiency as C++ in high-performance scenarios. Therefore, Verificxx was conceived both as an experiment and as a potentially faster and more robust tool for massive data validation, taking advantage of C++’s compilation speed, optimization capabilities, and more precise memory management. Additionally, the project served as an opportunity to explore how to apply solid design patterns and software engineering best practices in C++, maintaining clean and modular code without sacrificing performance.

During development, several challenging design decisions had to be made. One key decision was how to present the API to users in an intuitive way, allowing access to the validation schema and rule execution without exposing the internal complexity of the SchemaManager or the column structures. To address this, the schema was fully encapsulated within the main validator class, so that users only need to interact with methods such as fromColumnSchema and execute, while the internal handling of the schema and rule logic remains transparent. Another important choice involved designing a flexible and type-safe error reporting system. A std::variant-based payload system was implemented to support different types of error messages, such as invalid characters, found substrings, or generic errors, preserving C++’s strong typing while avoiding indiscriminate use of strings.

In conclusion, Verificxx combines solid design patterns, hexagonal architecture, clean code principles, and the efficiency of C++ to provide a flexible, robust, and scalable data validation library. The tool can handle both simple cases and massive data processing scenarios, encapsulating the complexity of schema and rule management while presenting a clean and safe API to the user. The project represents not only a technical solution but also a careful design exercise, balancing usability, maintainability, and performance, and demonstrating how advanced software engineering practices can be applied to C++ in a practical, real-world context.

## TODO

#### Currently, Verificxx supports validation of individual string values and column-based validation using predefined rules or JSON-defined schemas. However, support for bulk data processing is not yet implemented. Future versions should allow users to load large datasets from CSV or JSON files and apply the corresponding column validation rules to each row automatically. This will enable seamless integration with data pipelines and facilitate validation of thousands of records efficiently.

## HOW TO USE

1. Clone the repository:
```bash
git clone https://github.com/username/verificxx.git
cd verificxx
```
2. Create a build directory and compile:
```bash
mkdir build && cd build
cmake ..
cmake --build .
```
3. Optional, run tests:
```bash
ctest --verbose
```

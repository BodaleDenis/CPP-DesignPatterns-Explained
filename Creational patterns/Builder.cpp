#include<iostream>
#include<memory>

class Employee
{
    int _badgeNumber;

    public:
        void setHoursContract (int badgeNumber) { _badgeNumber = badgeNumber; }
        int getHoursContract () { return _badgeNumber; }
};

class Contractor
{
    int _ownCompanybadge;

    public:
        void setOwnCompanybadge (int ownCompanybadge) { _ownCompanybadge = ownCompanybadge; }
        int getOwnCompanybadge () { return _ownCompanybadge; }
};

class Auxiliar
{
    int _registrationID;

    public:
        void setRegistrationID (int registrationID) { _registrationID = registrationID; }
        int getRegistrationID () { return _registrationID; }
};

class Company
{
    public:
        Employee _employee;
        Contractor _contractor;
        Auxiliar _auxiliar;
};

class ICompanyFirst
{
    protected:
        std::unique_ptr<Company> _company;
    public:
        virtual void buildEmployee() = 0;
        virtual void buildContractor() = 0;
        virtual void buildAuxiliar() = 0;
        virtual std::unique_ptr<Company> getCompany() = 0;
};

class CompanyFirstDepartmentA : public ICompanyFirst
{
    public:
        CompanyFirstDepartmentA() { _company.reset(new Company); }
        ~CompanyFirstDepartmentA() = default;
        void buildEmployee() { _company->_employee.setHoursContract(8); }
        void buildContractor() { _company->_contractor.setOwnCompanybadge(222); }
        void buildAuxiliar() { _company->_auxiliar.setRegistrationID(1222); }
        std::unique_ptr<Company> getCompany()
        {
            std::cout << "FirstCompanyDepartmentA is init" << std::endl;
            return std::move(_company);
        }
};

class CompanyFirstDepartmentB : public ICompanyFirst
{
    public:
        CompanyFirstDepartmentB() { _company.reset(new Company); }
        ~CompanyFirstDepartmentB() = default;
        void buildEmployee() { _company->_employee.setHoursContract(6); }
        void buildContractor() { _company->_contractor.setOwnCompanybadge(111); }
        void buildAuxiliar() { _company->_auxiliar.setRegistrationID(2111); }
        std::unique_ptr<Company> getCompany()
        {
            std::cout << "FirstCompanyDepartmentB is init" << std::endl;
            return std::move(_company);
        }
};

class Director
{
    std::unique_ptr<ICompanyFirst>_companyBuilder;
    public:
        Director() = default;
        void setBuilder(std::unique_ptr<ICompanyFirst> &build)
        {
            _companyBuilder.reset(build.release());
        }
        void constructCompany()
        {
            _companyBuilder->buildEmployee();
            _companyBuilder->buildContractor();
            _companyBuilder->buildAuxiliar();
        }
        std::unique_ptr<Company> getCompany()
        {
            std::cout << "Get company in Director" << std::endl;
            return std::move(_companyBuilder->getCompany());
        }
};

int main()
{
    std::cout << "Builder Design Pattern" << std::endl;
    std::cout << "Using FirstCompanyDepartmentA builder" << std::endl;
    std::unique_ptr<ICompanyFirst>build { new CompanyFirstDepartmentA};
    std::unique_ptr<Director>dir{new Director};
    dir->setBuilder(build);
    dir->constructCompany();
    std::unique_ptr<Company> comp {dir->getCompany()};
    std::cout << "Hours nr:" << (*comp)._employee.getHoursContract() << std::endl;
    std::cout << "Company badge nr:" << (*comp)._contractor.getOwnCompanybadge() << std::endl;
    std::cout << "RegistrationId nr:" << (*comp)._auxiliar.getRegistrationID() << std::endl;
    
    std::cout << "Using FirstCompanyDepartmentB builder" << std::endl;
    build.reset(new CompanyFirstDepartmentB);
    dir->setBuilder(build);
    dir->constructCompany();
    comp.reset(dir->getCompany().release());
    std::cout << "Hours nr:" << (*comp)._employee.getHoursContract() << std::endl;
    std::cout << "Company badge nr:" << (*comp)._contractor.getOwnCompanybadge() << std::endl;
    std::cout << "RegistrationId nr:" << (*comp)._auxiliar.getRegistrationID() << std::endl;
    return 0;
}

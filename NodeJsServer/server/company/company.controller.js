const Company = require('./company.model');
const Coupon = require('../coupon/coupon.model');

/**
 * Load company and append to req.
 */

function load(req, res, next, id) {
  Company.get(id)
    .then((company) => {
      req.company = company; // eslint-disable-line no-param-reassign
      return next();
    })
    .catch(e => next(e));
}

/**
 * Get company
 * @returns {Company}
 */
function get(req, res) {
  return res.json(req.company);
}

/**
 * Get company with details
 * @returns {company: Company, coupons: [Coupon]}
 */
function getDetails(req, res) {
  var result = req.company;
  Coupon.find({ownerCompany: req.company._id}).exec(
    function(err, coupons) {
      result["coupons"] = coupons;
      res.json(result);
    }
  );
}

/**
 * Create new company
 * @property {string} req.body.name  - The name of company.
 * @property {string} req.body.information - The category of company.
 * @returns {Company}
 */

function create(req, res, next) {
  const company = new Company({
    name: req.body.name,
    information: req.body.information
  });

  if (req.body.loc) company.loc = req.body.loc;
  else company.loc = null;

  if (req.body.category) company.category = req.body.category;
  else company.category = null;

  company.save()
    .then(savedCompany => res.json(savedCompany))
    .catch(e => next(e));
}

/**
 * Update existing company
 * @property {string} req.body.name - The name of company.
 * @property {string} req.body.information  - The information of company.
 * @returns {Company}
 */
function update(req, res, next) {
  const company = req.company;

  if (req.body.title)
    company.title = req.body.title;
  if(req.body.information)
    company.information = req.body.information;
  if (req.body.loc)
    company.loc = req.body.loc;
  if (req.body.category)
    company.category = req.body.category;

  company.save()
    .then(savedCompany => res.json(savedCompany))
    .catch(e => next(e));
}

/**
 * Get company list.
 * @property {number} req.query.skip - Number of users to be skipped.
 * @property {number} req.query.limit - Limit number of users to be returned.
 * @returns {Company[]}
 */
function list(req, res, next) {
  const { limit = 50, skip = 0 } = req.query;
  if (req.query.loctype
      && req.query.long
      && req.query.lat) {
      Company.find(
            {
              "loc": {
              "$nearSphere" :{
                "$geometry":  {
                  "type": req.query.loctype,
                  "coordinates": [req.query.long, req.query.lat]
                },
                "$maxDistance":  req.query.maxDistance ? req.query.maxDistance : 10000,
              }}
            }
        , function (err, companies) {
            if (err) {
              next (err);
            }
            else {
              Company.find({"loc": null}, function (err, companies_without_loc) {
                if (err) {
                  next(err);
                } else {
                  res.json(companies.concat(companies_without_loc));
                }
              })
            }
        }
      );
  }
  else  {
      Company.list({ limit, skip })
        .then(companies => res.json(companies))
        .catch(e => next(e));
  }
}



/**
 * Delete company.
 * @returns {Company}
 */
function remove(req, res, next) {
  const company = req.company;
  company.remove()
    .then(deletedCompany => res.json(deletedCompany))
    .catch(e => next(e));
}

module.exports = { load, get, getDetails, create, update, list, remove };

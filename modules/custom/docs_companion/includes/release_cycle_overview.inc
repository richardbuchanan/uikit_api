<p>Following in the footsteps of Drupal and the release of Drupal 8.0.0, the UIkit project maintainers are committing themselves to a release cycle schedule in order to meet the growing demand and interest in UIkit for Drupal. This document describes the release cycle for all versions of UIkit (including UIkit 7 and 8) from August 26, 2016 on.</p>

<h2 id="key_dates" class="docs-link-anchor">
  <a href="#key_dates" class="uk-link-reset">Key dates <i class="uk-icon-link uk-text-muted"></i></a>
</h2>
<p>The minor version numbers in this table assume there are no unscheduled minors. If an unscheduled minor is released, the dates will not change, but subsequent minor version numbers will be incremented accordingly. Minor versions will always match the major version of the UIkit framework the branch supports.</p>

<h3>Monthly</h3>
<div class="uk-overflow-container">
  <table class="uk-table uk-table-hover uk-table-striped uk-table-condensed">
    <tbody>
    <tr>
      <td class="uk-width-3-10">First Wednesday of every month</td>
      <td class="uk-width-7-10">Bugfix release window for <em>UIkit 7.x-2.x</em>, <em>7.x-3.x</em> and <em>8.x-2.x</em></td>
    </tr>
    <tr>
      <td class="uk-width-3-10">Third Wednesday of every month</td>
      <td class="uk-width-7-10">Security release window for <em>UIkit 7.x-2.x</em>, <em>7.x-3.x</em> and <em>8.x-2.x</em></td>
    </tr>
    </tbody>
  </table>
</div>

<h3>Past milestones</h3>
<div class="uk-overflow-container">
  <table class="uk-table uk-table-hover uk-table-striped uk-table-condensed">
    <tbody>
    <tr>
      <td class="uk-width-3-10">August 26, 2016</td>
      <td class="uk-width-7-10"><em>UIkit 7.x-2.x</em> enters development stage</td>
    </tr>
    <tr>
      <td class="uk-width-3-10">March 15, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 7.x-3.x</em> enters development stage</td>
    </tr>
    <tr>
      <td class="uk-width-3-10">March 19, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 8.x-2.x</em> enters development stage</td>
    </tr>
    <tr>
      <td class="uk-width-3-10">April 5, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 7.x-2.0</em> released</td>
    </tr>
    <tr>
      <td class="uk-width-3-10">April 7, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 7.x-2.1</em> released (due to packaging errors)</td>
    </tr>
    <tr>
      <td class="uk-width-3-10">April 17, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 7.x-2.2</em> released</td>
    </tr>
    </tbody>
  </table>
</div>

<h3>Current development cycle</h3>
<div class="uk-overflow-container">
  <table class="uk-table uk-table-hover uk-table-striped uk-table-condensed">
    <tbody>
    <tr>
      <td class="uk-width-3-10">Week of April 24, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 8.x-2.0</em> and <em>UIkit 7.x-2.3-beta1</em> released</td>
    </tr>
    <tr>
      <td class="uk-width-3-10">Week of May 8, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 7.x-3.0-beta2</em> released (stays in beta until UIkit framework v3.0.0 leaves beta)<em> and UIkit 8.x-3.x-dev</em> opened</td>
    </tr>
    <tr>
      <td class="uk-width-3-10">Week of May 22, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 7.x-2.3-rc1</em> and <em>UIkit 8.x-2.1-beta1</em> released</td>
    </tr>
    <tr>
      <td class="uk-width-3-10">Week of June 5, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 7.x-3.0-beta3</em> and <em>UIkit 8.x-3.0-beta1</em> released</td>
    </tr>
    <tr>
      <td class="uk-width-3-10">Week of June 19, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 7.x-2.3</em> and <em>UIkit 8.x-2.1-rc1</em> released</td>
    </tr>
    <tr>
      <td class="uk-width-3-10">Week of July 3, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 7.x-3.0-beta4</em> and <em>UIkit 8.x-3.0-rc1</em> released</td>
    </tr>
    <tr>
      <td class="uk-width-3-10">Week of July 17, 2017</td>
      <td class="uk-width-7-10"><em>UIkit 8.x-2.1</em> released and <em>UIkit 7.x-2.4-dev</em> opened</td>
    </tr>
    </tbody>
  </table>
</div>

<h2 id="overview" class="docs-link-anchor">
  <a href="#overview" class="uk-link-reset">Overview of release schedule <i class="uk-icon-link uk-text-muted"></i></a>
</h2>
<p>New releases and opened development branches will be released bi-weekly, with <em>UIkit 7.x-2.x/UIkit 8.x-2.x</em> branches one bi-weekly cycle and <em>UIkit 7.x-3.x/UIkit 8.x-3.x</em> branches the other bi-weekly cycle. This will allow the maintainers to focus on a single UIkit framework version at a time. The only exception to this will be critical/security releases. This cycle may change in the future based on development needs.</p>

<h3>Key considerations for future major releases:</h3>
<ul>
  <li>Once UIkit framework v3.0.0 is released we will change the release cycle above so <em>UIkit 7.x-3.0</em> and <em>UIkit 8.x-3.0</em> are released together.</li>
  <li>Subsequent releases on the <em>UIkit 7.x-3.x</em> and <em>UIkit 8.x-3.x</em> branches will be released together in the same release stages (i.e. <em>UIkit 7.x-3.1-dev</em> and <em>UIkit 8.x-3.1-dev</em> will be opened the same week).</li>
  <li>The <em>UIkit 7.x-2.x</em> and <em>UIkit 8.x-2.x</em> will then enter a feature freeze and also be released together in the same release stages (i.e. <em>UIkit 7.x-2.5-dev</em> and <em>8.x-2.2-dev</em> will be opened the same week).</li>
  <li>Once the feature freeze on the <em>UIkit 7.x-2.x</em> and <em>UIkit 8.x-2.x</em> branches is in place only critical and security fixes will be considered. We will continue to support these branches but will also shift our main focus to the <em>UIkit 7.x-3.x</em> and <em>UIkit 8.x-3.x</em> branches.</li>
  <li>Any modules or sub-themes released by the maintainers of UIkit will also keep in mind the above under considerations during development of those projects. This will allow all supported modules and themes to align their development with UIkit base theme project.</li>
  <li>If the UIkit framework opens a v4.x.x release, the <em>UIkit 7.x-2.x</em> and <em>UIkit 8.x-2.x</em> branches will enter an End of Life cycle. Once v4.0.0 is released <em>UIkit 7.x-2.x</em> and <em>UIkit 8.x-2.x</em> will then become unsupported and their releases removed from the UIkit project page.</li>
  <li>Following the above point, the maintainers will always support the two most current UIkit framework versions so themers and developers can prepare their projects for upgrades to the latest framework version. Those who do not update their projects before the End of Life will have their projects removed from the supported modules and themes section of the UIkit project page.</li>
</ul>

<h3>Key considerations for future minor releases:</h3>
<ul>
  <li>Beginning with <em>UIkit 7.x-3.0</em> and <em>UIkit 8.x-3.0</em>, each minor release will have a development, beta and release candidate stage. Alpha stages will no longer be used beyond this point.</li>
  <li>The primary purpose of the release candidate phase is to stabilize the minor version for release. Any new features which do not make it into the next minor release will be moved the subsequent minor release.</li>
  <li>There will be a minimum of 1 month between the release of a new minor release and public disclosure of any security issues that affect the previous minor, in order to ensure all sites have adequate time to upgrade. This follows Drupal's guidelines for public disclosure of security issues.</li>
  <li>An open feature development phase for each minor version may begin when the branch is opened, or may begin later, depending on critical and major technical debt for the branch.</li>
</ul>

<p><strong>Note</strong>: It is important to keep the update module enabled to ensure you receive updates in a timely manner. Otherwise, be sure to enable the update module and check for updates at least twice a month.</p>